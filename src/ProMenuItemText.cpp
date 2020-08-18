#include "ProMenuItemText.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItemText::MenuItemText(int id, char *name, MenuItemTextInterface &interface, char *prefix):
    MenuItemEdit(id, name, prefix),
    interface(interface)
{

}

void MenuItemText::redraw()
{
    this->MenuItemEdit::redraw();
    this->redrawCursor = true;
}

bool MenuItemText::select()
{
    this->MenuItemEdit::select();
    this->cursorPos = 0;
    this->startPos = -1;
    this->editMode = false;
    return true;
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
        this->redrawCursor = true;
    } else {
        if (this->cursorPos > -1) {
            this->cursorPos--;
            this->redrawCursor = true;
            if ((this->cursorPos - this->startPos < 0) && (this->startPos > -1)) {
                this->startPos--;
                this->redrawValue = true;
            }
        } else {
            return false;
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
        this->redrawCursor = true;
    } else {
        if (ch != 0) {
            this->cursorPos++;
            this->redrawCursor = true;
            if (this->cursorPos - this->startPos >= this->getMenuManager().getDisplay().getWidth()) {
                this->startPos++;
                this->redrawValue = true;
            }
        } else {
            this->interface.setChar(*this, this->cursorPos, ' ');
            ch = this->interface.getChar(*this, this->cursorPos);
            if (ch != 0) {
                this->cursorPos++;
                this->redrawCursor = true;
                this->redrawValue = true;
                if (this->cursorPos - this->startPos >= this->getMenuManager().getDisplay().getWidth()) {
                    this->startPos++;
                }
            } else {
                return false;
            }
        }
    }
    return true;
}

bool MenuItemText::enter()
{
    char ch;
    if (this->editMode != false) {
        this->editMode = false;
        this->redrawCursor = true;
    } else {
        if (this->cursorPos < 0) {
            this->interface.save(*this);
            return this->Menu::exit();
        } else {
            ch = this->interface.getChar(*this, this->cursorPos);
            if (ch == 0) {
                if (this->cursorPos > 0) {
                    this->cursorPos--;
                    this->redrawCursor = true;
                    this->redrawValue = true;
                    this->interface.setChar(*this, this->cursorPos, 0);

                    if (this->startPos > -1)
                        this->startPos--;
                } else {
                    return false;
                }
            } else {
                this->editMode = true;
                this->redrawCursor = true;
            }
        }
    }
    return true;
}

void MenuItemText::renderScroll(DisplayInterface &display)
{
    this->MenuItemEdit::renderScroll(display);
    this->redrawCursor = true;
}

void MenuItemText::renderValue(DisplayInterface &display)
{
    char ch;
    int pos = this->startPos;
    int x = 0;
    int y = 0;
    bool pad = false;

    if (display.getHeight() > 1)
        y = 1;

    display.setCursor(0, y);
    for (x = 0; x < display.getWidth(); x++) {
        if ((x == 0) && (this->startPos == -1)) {
            display.printChar('>');
            pos++;
        } else {
            if (pad == false) {
                ch = this->interface.getChar(*this, pos++);
                if (ch != 0) {
                    display.printChar(ch);
                } else {
                    display.printChar('<');
                    pad = true;
                }             
            } else {
                display.printChar(' ');
            }
        }
    }
}

void MenuItemText::renderCursor(DisplayInterface &display)
{
    int pos;
    int y = 0;
    char ch;

    if (display.getHeight() > 1)
        y = 1;
    
    pos = this->cursorPos - this->startPos;
    
    if (this->cursorPos >= 0) {
        ch = this->interface.getChar(*this, this->cursorPos);
        if (ch != 0)
            display.setChar(pos, y, ch);
    }

    if (this->editMode != false) {
        display.selectChar(pos, y);
    } else {
        display.deselectChar();
    }
    display.showCursor(pos, y);
}

void MenuItemText::render(DisplayInterface &display)
{
    this->MenuItemEdit::render(display);

    if (this->redrawCursor) {
        this->redrawCursor = false;
        this->renderCursor(display);
    }
}

MenuItemEditInterface& MenuItemText::getInterface()
{
    return this->interface;
}

};