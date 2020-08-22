#ifndef PRO_MENU_VALUE_TEXT_MANAGER_H
#define PRO_MENU_VALUE_TEXT_MANAGER_H

#include "ProMenuItemText.h"

#include <stddef.h>

namespace promenu::managers {

class ValueTextManager: public MenuItemTextInterface {

public:
    using LoadHandler = void (*)(int id, char *text, int maxLength);
    using SaveHandler = void (*)(int id, char *text, int maxLength);

    struct TextDescriptor {
        char *text;
        int maxLength;
    };

    ValueTextManager(struct TextDescriptor *descriptors, int valuesNum, LoadHandler loadHandler, SaveHandler saveHandler);

    virtual void load(MenuItem &item);
    virtual int getMaxLength(MenuItem &item);
    virtual void setChar(MenuItem &item, int p, char ch);
    virtual char getChar(MenuItem &item, int p);
    virtual void save(MenuItem &item);
    virtual void cancel(MenuItem &item);

private:
    LoadHandler loadHandler;
    SaveHandler saveHandler;

    struct TextDescriptor *descriptors;
    const int valuesNum;
};

};

#endif /* PRO_MENU_VALUE_TEXT_MANAGER_H */
