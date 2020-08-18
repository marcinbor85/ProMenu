#include "ProMenuActionManager.h"

namespace promenu::managers {

ActionManager::ActionManager(ActionHandler handler):
    handler(handler)
{

}

bool ActionManager::action(MenuItemAction &item)
{
    int i = item.getId();
    return this->handler(i);
}

};