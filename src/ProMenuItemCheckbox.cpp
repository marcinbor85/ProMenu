#include "ProMenuItemCheckbox.h"
#include "ProMenu.h"

namespace promenu {

void MenuItemCheckbox::select(MenuManager *manager) {
    this->interface.setSelected(!this->interface.isSelected());
}

void MenuItemCheckbox::getDisplayText(char *text, int maxSize) {
    strncpy(text, "[", maxSize);
    strncat(text, (this->interface.isSelected() == false) ? " " : "x", maxSize - 1);
    strncat(text, "]", maxSize - 2);    
    strncat(text, this->getName(), maxSize - 3);
}

};