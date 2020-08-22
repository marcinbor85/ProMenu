#include "ProMenuValueNumberManager.h"

#include <stddef.h>
#include <stdio.h>

namespace promenu::managers {

ValueNumberManager::ValueNumberManager(struct NumberDescriptor *descriptors, int valuesNum, LoadHandler loadHandler, SaveHandler saveHandler):
    descriptors(descriptors),
    valuesNum(valuesNum),
    loadHandler(loadHandler),
    saveHandler(saveHandler)
{

}

void ValueNumberManager::load(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum) {
        this->loadHandler(i, this->descriptors[i].value);
    }
}

bool ValueNumberManager::prevValue(MenuItem &item)
{
    int i = item.getId();
    long val;
    if (i < this->valuesNum) {
        if (this->isPrevValueAvailable(item)) {
            val = *this->descriptors[i].value;
            *this->descriptors[i].value = val - 1;
            return true;
        }
    }
    return false;
}

bool ValueNumberManager::nextValue(MenuItem &item)
{
    int i = item.getId();
    long val;
    if (i < this->valuesNum) {
        if (this->isNextValueAvailable(item)) {
            val = *this->descriptors[i].value;
            *this->descriptors[i].value = val + 1;
            return true;
        }
    }
    return false;
}

void ValueNumberManager::getValueText(MenuItem &item, char *text, int maxSize)
{
    int i = item.getId();
    if (i < this->valuesNum) {
        snprintf(text, maxSize, "%ld", *this->descriptors[i].value);
    } else {
        if (maxSize > 0)
            text[0] = 0;
    }
}

void ValueNumberManager::save(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum) {
        this->saveHandler(i, *this->descriptors[i].value);
    }
}

void ValueNumberManager::cancel(MenuItem &item)
{
    this->load(item);
}

bool ValueNumberManager::isPrevValueAvailable(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum)
        return (*this->descriptors[i].value > this->descriptors[i].min);
    return false;
}

bool ValueNumberManager::isNextValueAvailable(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum)
        return (*this->descriptors[i].value < this->descriptors[i].max);
    return false;
}

};