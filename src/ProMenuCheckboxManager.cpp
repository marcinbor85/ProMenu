#include "ProMenuCheckboxManager.h"

namespace promenu::managers {

CheckboxManager::CheckboxManager(bool *values, int valuesNum, LoadHandler loadHandler, SaveHandler saveHandler):
    values(values),
    valuesNum(valuesNum),
    loadHandler(loadHandler),
    saveHandler(saveHandler)
{

}

bool CheckboxManager::isSelected(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum)
        return this->values[i];
    return false;
}

bool CheckboxManager::setSelected(MenuItem &item, bool val)
{
    int i = item.getId();
    if (i < this->valuesNum)
        this->values[i] = val;
    return false;
}

void CheckboxManager::load(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum)
        this->loadHandler(i, &this->values[i]);
}

void CheckboxManager::save(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum)
        this->saveHandler(i, this->values[i]);
}

};