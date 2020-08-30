#ifndef PRO_MENU_SCROLL_LINE_H
#define PRO_MENU_SCROLL_LINE_H

#include <stddef.h>

namespace promenu {

class ScrollLine {

public:
    ScrollLine();

    void reset();
    void scroll(int lineLength, int xMax);
    int getPosition();
    bool isRedraw();
    void setRedraw(bool state);

private:
    unsigned long lastTick;
    unsigned long timeout;
    int pos;
    bool redraw;

    static constexpr unsigned long SCROLL_START_TIMEOUT = 2000UL;
    static constexpr unsigned long SCROLL_TIMEOUT = 500UL;
};

};

#endif /* PRO_MENU_SCROLL_LINE_H */
