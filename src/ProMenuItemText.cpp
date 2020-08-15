#include "ProMenuItemText.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItemText::MenuItemText(int id, char *name, MenuItemTextInterface &interface):
    MenuItem(id, name),
    Menu(id, name, NULL, 0),
    interface(interface)
{

}

bool MenuItemText::select()
{
    this->interface.init(*this);
    this->menu->getMenuManager().enterToMenu(*this);
    this->cursorPos = 0;
    this->startPos = 0;
    this->editMode = false;
    return true;
}

void MenuItemText::getRenderName(char *text, int maxSize)
{
    snprintf(text, maxSize, "%s...", this->MenuItem::name);
}

bool MenuItemText::prev()
{
    char ch;
    ch = this->interface.getChar(*this, this->cursorPos);
    if (this->editMode != false) {
        if (ch == 32) {
            ch = 127;
        } else {
            ch--;
        }
        this->interface.setChar(*this, this->cursorPos, ch);
    } else {
        if (this->cursorPos > 0) {
            this->cursorPos--;
            if (this->cursorPos + 1 - this->startPos == 0)
                this->startPos--;
        } else {
            if (this->cursorPos == 0)
                this->cursorPos--;
        }
    }
    return true;
}

bool MenuItemText::next()
{
    char ch;
    ch = this->interface.getChar(*this, this->cursorPos);
    if (this->editMode != false) {
        if (ch == 127) {
            ch = 32;
        } else {
            ch++;
        }
        this->interface.setChar(*this, this->cursorPos, ch);
    } else {
        if (ch != 0) {
            this->cursorPos++;

            ch = this->interface.getChar(*this, this->cursorPos);
            if (ch != 0) {
                if (this->cursorPos - this->startPos >= this->getMenuManager().getDisplay().getWidth() - 2) {
                    this->startPos++;
                }
            }
        } else {
            this->interface.setChar(*this, this->cursorPos, ' ');
            ch = this->interface.getChar(*this, this->cursorPos);
            if (ch != 0) {
                this->cursorPos++;
                if (this->cursorPos - this->startPos >= this->getMenuManager().getDisplay().getWidth() - 2) {
                    this->startPos++;
                }
            }
        }
    }
    return true;
}

bool MenuItemText::exit()
{
    this->interface.cancel(*this);
    this->end();
    return true;
}

bool MenuItemText::enter()
{
    char ch;
    if (this->editMode != false) {
        this->editMode = false;
    } else {
        if (this->cursorPos < 0) {
            this->interface.save(*this);
            this->end();
        } else {
            ch = this->interface.getChar(*this, this->cursorPos);
            if (ch == 0) {
                if (this->cursorPos > 0) {
                    this->cursorPos--;
                    this->interface.setChar(*this, this->cursorPos, 0);

                    if (this->startPos > 0) {
                        if (this->cursorPos + 1 - this->startPos >= this->getMenuManager().getDisplay().getWidth() - 2)
                            this->startPos--;
                    }
                }
            } else {
                this->editMode = true;
            }
        }
    }
    return true;
}

void MenuItemText::render(DisplayInterface &display)
{
    char line[display.getWidth()];
    char ch;
    int pos;
    int i;
    int y = 0;

    display.clear();

    if (display.getHeight() > 1) {
        strncpy(line, this->MenuItem::name, sizeof(line));
        display.setText(0, 0, line);
        y++;
    }

    display.setCursor(0, y);
    display.printText(">");
    for (i = 0; i < sizeof(line) - 2; i++) {
        pos = this->startPos + i;
        ch = this->interface.getChar(*this, pos);
        if (ch == 0)
            break;
        display.printText(&ch);
    }
    display.printText("<");

    pos = this->cursorPos + 1 - this->startPos;
    if (this->editMode != false) {
        display.selectChar(pos, y);
    } else {
        display.showCursor(pos, y);
    }
}

};