#include "../libs/raylib/src/raylib.h"
#include "../libs/raylib/src/raymath.h"
#include "math.hpp"
#include <vector>

enum PlatformRotation {
    INDEPENDENT,
    FIXED,
    ADDITIVE
};

class Platform {
    public:
        int x;
        int y;
        int width;
        int height;
        Color border_color;
        Color fill_color;
        float init_angle;
        float angle;
        int line_thickness;
        PlatformRotation rotation;
        Platform *parent;
        Texture2D border_color_texture;
        Texture2D fill_color_texture;
        
        Platform(int x, int y, int width, int height, Color border_color, Color fill_color, float angle, int line_thickness) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
            this->border_color = border_color;
            this->fill_color = fill_color;
            this->init_angle = angle;
            this->angle = angle;
            this->line_thickness = line_thickness;
            this->rotation = INDEPENDENT;
            
            // TODO: optimize such that all platforms share the same texture if possible
            this->border_color_texture = LoadTextureFromImage(GenImageColor(this->width, this->height, this->border_color));
            this->fill_color_texture = LoadTextureFromImage(GenImageColor(this->width, this->height, this->fill_color));
        }
        
        void attach(Platform *platform, PlatformRotation rotation) {
            this->parent = platform;
            this->rotation = rotation;
        }
        
        void detach() {
            this->parent = nullptr;
            this->rotation = INDEPENDENT;
        }
        
        void rotate(int degrees) {
            this->angle += degrees;
        }
        
        void move(int dx, int dy) {
            this->x += dx;
            this->y += dy;
        }
        
        void enlarge(int dw, int dh) {
            this->width += dw;
            this->height += dh;
        }
        
        void scale(int wm, int hm) {
            this->width *= wm;
            this->height *= hm;
        }
        
        void updateAngle() {
            switch (this->rotation) {
                case INDEPENDENT:
                    break;
                case FIXED:
                    this->angle = this->parent->angle;
                    break;
                case ADDITIVE:
                    this->angle = this->parent->angle + this->init_angle;
                    break;
            }
        }
        
        std::vector<Vector2> getOuterPoints() {
            return getOuterPoints(true);
        }
        
        std::vector<Vector2> getInnerPoints() {
            std::vector<Vector2> outer_points = getOuterPoints(false);
        
            return getInnerPoints(outer_points);
        }
        
        // TODO: review logic
        Vector2 getCenterPoint() {
            return Vector2{static_cast<float>(this->x), static_cast<float>(this->y)};
        }
        
        Vector2 getEndPosition() {
            std::vector<Vector2> outer_points = getOuterPoints();
            Vector2 point1 = outer_points[1];
            Vector2 point2 = outer_points[2];
            return Vector2{Lerp(point1.x, point2.x, 0.5f), Lerp(point1.y, point2.y, 0.5f)};
        }
        
        void draw() {
            if (this->parent != nullptr) {
                Vector2 parentEndPos = this->parent->getEndPosition();
                this->x = static_cast<int>(parentEndPos.x);
                this->y = static_cast<int>(parentEndPos.y);
            }
            
            std::vector<Vector2> outer_points = getOuterPoints();
            std::vector<Vector2> inner_points = getInnerPoints();
            
            DrawTexturePoly(border_color_texture, getCenterPoint(), outer_points.data(), outer_points.data(), outer_points.size(), this->border_color);
            DrawTexturePoly(fill_color_texture, getCenterPoint(), inner_points.data(), inner_points.data(), inner_points.size(), this->fill_color);
        }
    
    private:
        std::vector<Vector2> getOuterPoints(bool rotate) {
            updateAngle();
            
            float origin_x = static_cast<float>(this->x);
            float origin_y = static_cast<float>(this->y);
            
            std::vector<Vector2> outer_points;
            
            outer_points.push_back(Vector2{origin_x, origin_y - static_cast<float>(this->width/2.0)}); // Outer top left
            outer_points.push_back(Vector2{origin_x + static_cast<float>(this->height), origin_y - static_cast<float>(this->width/2.0)}); // Outer top right
            outer_points.push_back(Vector2{origin_x + static_cast<float>(this->height), origin_y + static_cast<float>(this->width/2.0)}); // Outer bottom right
            outer_points.push_back(Vector2{origin_x, origin_y + static_cast<float>(this->width/2.0)}); // Outer bottom left
            
            // Rotating points
            if (rotate) {
                int i = 0;
                for (Vector2 point : outer_points) {
                    outer_points[i] = rotateVector(point, Vector2{origin_x, origin_y}, this->angle);
                    i++;
                }
            }
            
            return outer_points;
        }
        
        std::vector<Vector2> getInnerPoints(std::vector<Vector2> outer_points, bool rotate = true) {
            updateAngle();
        
            float origin_x = static_cast<float>(this->x);
            float origin_y = static_cast<float>(this->y);
            
            std::vector<Vector2> inner_points;
            
            inner_points.push_back(Vector2{outer_points[0].x + this->line_thickness, outer_points[0].y + this->line_thickness}); // Inner bottom left
            inner_points.push_back(Vector2{outer_points[1].x - this->line_thickness, outer_points[1].y + this->line_thickness}); // Inner top right
            inner_points.push_back(Vector2{outer_points[2].x - this->line_thickness, outer_points[2].y - this->line_thickness}); // Inner bottom right
            inner_points.push_back(Vector2{outer_points[3].x + this->line_thickness, outer_points[3].y - this->line_thickness}); // Inner bottom left
            
            // Rotating points
            if (rotate) {
                int i = 0;
                for (Vector2 point : inner_points) {
                    inner_points[i] = rotateVector(point, Vector2{origin_x, origin_y}, this->angle);
                    i++;
                }
            }
            
            return inner_points;
        }
};