#ifndef PRO_MENU_DISPLAY_H
#define PRO_MENU_DISPLAY_H

namespace promenu {

class DisplayInterface {

public:
    DisplayInterface(int width, int height):
        width(width),
        height(height) {};

    virtual void setText(int x, int y, const char *text) = 0;
    virtual void clear() = 0;
    virtual void begin() {};
    virtual void end() {};

    int getWidth() { return this->width; };
    int getHeight() { return this->height; };
    
private:
    DisplayInterface() = delete;
    DisplayInterface(const DisplayInterface&) = delete;
    DisplayInterface& operator=(const DisplayInterface&) = delete;

    const int width;
    const int height;
};

};

#endif /* PRO_MENU_DISPLAY_H */
