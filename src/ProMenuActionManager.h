#ifndef PRO_MENU_ACTION_MANAGER_H
#define PRO_MENU_ACTION_MANAGER_H

#include "ProMenuItemAction.h"

#include <stddef.h>

namespace promenu::managers {

class ActionManager: public MenuItemActionInterface {

public:
    using ActionHandler = bool (*)(int id);
    ActionManager(ActionHandler handler);

    virtual bool action(MenuItemAction &item);

private:
    const ActionHandler handler;
};

};

#endif /* PRO_MENU_ACTION_MANAGER_H */
