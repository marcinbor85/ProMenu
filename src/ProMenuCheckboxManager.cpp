#include "ProMenuCheckboxManager.h"

namespace promenu::managers {

CheckboxManager::CheckboxManager(bool *values, int valuesNum):
    values(values),
    valuesNum(valuesNum)
{

}

bool CheckboxManager::isSelected(MenuItemCheckbox &item)
{
    int i = item.getId();
    if (i < this->valuesNum)
        return this->values[i];
    return false;
}

bool CheckboxManager::setSelected(MenuItemCheckbox &item, bool val)
{
    int i = item.getId();
    if (i < this->valuesNum)
        this->values[i] = val;
    return false;
}

};