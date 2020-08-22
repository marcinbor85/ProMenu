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
            *this->descriptors[i].value = val - this->descriptors[i].step;
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
            *this->descriptors[i].value = val + this->descriptors[i].step;
            return true;
        }
    }
    return false;
}

void ValueNumberManager::getValueText(MenuItem &item, char *text, int maxSize)
{
    int i = item.getId();
    long valInt;
    unsigned long valDec;
    long val;
    long div;
    char sign[2];
    char formatString[16];
    if (i < this->valuesNum) {
        val = *this->descriptors[i].value;
        if (this->descriptors[i].decimalPlaces == 0) {
            snprintf(text, maxSize, "%ld", val);
        } else {
            div = 1;
            for (int n = 0; n < this->descriptors[i].decimalPlaces; n++)
                div *= 10;
                
            if (val < 0) {
                val = -val;
                sign[0] = '-';
                sign[1] = 0;
            } else {
                sign[0] = 0;
            }

            valInt = val / div;
            valDec = val % div;
            snprintf(formatString, sizeof(formatString), "%s%%ld.%%0%dlu", sign, this->descriptors[i].decimalPlaces);
            snprintf(text, maxSize, formatString, valInt, valDec);
        }        
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