#ifndef PRO_MENU_DISPLAY_H
#define PRO_MENU_DISPLAY_H

namespace promenu {

class DisplayInterface {

public:
    DisplayInterface(int width, int height);

    virtual void setCursor(int x, int y) = 0;
    virtual void printText(const char *text) = 0;
    virtual void setText(int x, int y, const char *text) = 0;
    virtual void selectChar(int x, int y) = 0;
    virtual void deselectChar() = 0;
    virtual void showCursor(int x, int y) = 0;
    virtual void hideCursor() = 0;
    virtual void clear() = 0;
    virtual void begin();
    virtual void end();

    virtual char getArrowUp();
    virtual char getArrowDown();
    virtual char getArrowUpDown();

    int getWidth();
    int getHeight();
    
private:
    DisplayInterface() = delete;
    DisplayInterface(const DisplayInterface&) = delete;
    DisplayInterface& operator=(const DisplayInterface&) = delete;

    const int width;
    const int height;
};

};

#endif /* PRO_MENU_DISPLAY_H */
