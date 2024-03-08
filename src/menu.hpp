#ifndef MENU_H
#define MENU_H

class Menu {
    public:
        Menu(Color borderColor, Color fillColor, Color textColor);
        void draw();
        void close();
    
    private:
        Color borderColor;
        Color fillColor;
        Color textColor;
};

#endif // MENU_H