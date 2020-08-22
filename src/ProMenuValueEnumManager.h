#ifndef PRO_MENU_VALUE_ENUM_MANAGER_H
#define PRO_MENU_VALUE_ENUM_MANAGER_H

#include "ProMenuItemValue.h"

#include <stddef.h>

namespace promenu::managers {

class ValueEnumManager: public MenuItemValueInterface {

public:
    using LoadHandler = void (*)(int id, int *value);
    using SaveHandler = void (*)(int id, int value);

    struct EnumDescriptor {
        char **enumText;
        int enumSize;
        int *value;
    };

    ValueEnumManager(struct EnumDescriptor *descriptors, int valuesNum, LoadHandler loadHandler, SaveHandler saveHandler);

    virtual void load(MenuItem &item);
    virtual bool prevValue(MenuItem &item);
    virtual bool nextValue(MenuItem &item);
    virtual void getValueText(MenuItem &item, char *text, int maxSize);
    virtual void save(MenuItem &item);
    virtual void cancel(MenuItem &item);
    virtual bool isPrevValueAvailable(MenuItem &item);
    virtual bool isNextValueAvailable(MenuItem &item);

private:
    LoadHandler loadHandler;
    SaveHandler saveHandler;

    struct EnumDescriptor *descriptors;
    const int valuesNum;
};

};

#endif /* PRO_MENU_VALUE_ENUM_MANAGER_H */
