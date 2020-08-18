#ifndef PRO_MENU_CHECKBOX_MANAGER_H
#define PRO_MENU_CHECKBOX_MANAGER_H

#include "ProMenuItemCheckbox.h"

#include <stddef.h>

namespace promenu::managers {

class CheckboxManager: public MenuItemCheckboxInterface {

public:
    explicit CheckboxManager(bool *values, int valuesNum);

    virtual bool isSelected(MenuItemCheckbox &item);
    virtual bool setSelected(MenuItemCheckbox &item, bool val);

private:
    CheckboxManager() = delete;
    CheckboxManager(const CheckboxManager&) = delete;
    CheckboxManager& operator=(const CheckboxManager&) = delete;

    bool *values;
    const int valuesNum;
};

};

#endif /* PRO_MENU_CHECKBOX_MANAGER_H */
