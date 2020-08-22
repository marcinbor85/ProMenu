#include "ProMenuValueEnumManager.h"

#include <stddef.h>
#include <stdio.h>

namespace promenu::managers {

ValueEnumManager::ValueEnumManager(struct EnumDescriptor *descriptors, int valuesNum, LoadHandler loadHandler, SaveHandler saveHandler):
    descriptors(descriptors),
    valuesNum(valuesNum),
    loadHandler(loadHandler),
    saveHandler(saveHandler)
{

}

void ValueEnumManager::load(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum) {
        this->loadHandler(i, this->descriptors[i].value);
    }
}

bool ValueEnumManager::prevValue(MenuItem &item)
{
    int i = item.getId();
    int val;
    if (i < this->valuesNum) {
        if (this->isPrevValueAvailable(item)) {
            val = *this->descriptors[i].value;
            *this->descriptors[i].value = val - 1;
            return true;
        }
    }
    return false;
}

bool ValueEnumManager::nextValue(MenuItem &item)
{
    int i = item.getId();
    int val;
    if (i < this->valuesNum) {
        if (this->isNextValueAvailable(item)) {
            val = *this->descriptors[i].value;
            *this->descriptors[i].value = val + 1;
            return true;
        }
    }
    return false;
}

void ValueEnumManager::getValueText(MenuItem &item, char *text, int maxSize)
{
    int i = item.getId();
    int val;
    if (i < this->valuesNum) {
        val = *this->descriptors[i].value;
        snprintf(text, maxSize, "%s", this->descriptors[i].enumText[val]);
    } else {
        if (maxSize > 0)
            text[0] = 0;
    }
}

void ValueEnumManager::save(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum) {
        this->saveHandler(i, *this->descriptors[i].value);
    }
}

void ValueEnumManager::cancel(MenuItem &item)
{
    this->load(item);
}

bool ValueEnumManager::isPrevValueAvailable(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum)
        return (*this->descriptors[i].value > 0);
    return false;
}

bool ValueEnumManager::isNextValueAvailable(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum)
        return (*this->descriptors[i].value < this->descriptors[i].enumSize - 1);
    return false;
}

};