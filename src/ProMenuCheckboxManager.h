#ifndef PRO_MENU_CHECKBOX_MANAGER_H
#define PRO_MENU_CHECKBOX_MANAGER_H

#include "ProMenuItemCheckbox.h"

#include <stddef.h>

namespace promenu::managers {

class CheckboxManager: public MenuItemCheckboxInterface {

public:
    using LoadHandler = void (*)(int id, bool *val);
    using SaveHandler = void (*)(int id, bool val);

    CheckboxManager(bool *values, int valuesNum, LoadHandler loadHandler, SaveHandler saveHandler);

    virtual bool isSelected(MenuItem &item);
    virtual bool setSelected(MenuItem &item, bool val);
    virtual void save(MenuItem &item);
    virtual void load(MenuItem &item);

private:
    LoadHandler loadHandler;
    SaveHandler saveHandler;

    bool *values;
    const int valuesNum;
};

};

#endif /* PRO_MENU_CHECKBOX_MANAGER_H */
