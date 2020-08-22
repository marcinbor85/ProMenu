#include "ProMenuValueTextManager.h"

#include <stddef.h>

namespace promenu::managers {

ValueTextManager::ValueTextManager(struct TextDescriptor *descriptors, int valuesNum, LoadHandler loadHandler, SaveHandler saveHandler):
    descriptors(descriptors),
    valuesNum(valuesNum),
    loadHandler(loadHandler),
    saveHandler(saveHandler)
{

}

void ValueTextManager::load(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum) {
        this->loadHandler(i, this->descriptors[i].text, this->descriptors[i].maxLength);
    }
}

int ValueTextManager::getMaxLength(MenuItem &item)
{
    int i = item.getId();
    if (i < this->valuesNum) {
        return this->descriptors[i].maxLength;
    }
    return 0;
}

void ValueTextManager::setChar(MenuItem &item, int p, char ch)
{
    int i = item.getId();
    if (i < this->valuesNum) {
        if (p < this->descriptors[i].maxLength)
           this->descriptors[i].text[p] = ch;
    }
}

char ValueTextManager::getChar(MenuItem &item, int p)
{
    int i = item.MenuItem::getId();
    if (i < this->valuesNum) {
        if (p < this->descriptors[i].maxLength)
            return this->descriptors[i].text[p];
    }
    return 0;
}

void ValueTextManager::save(MenuItem &item)
{
    int i = item.MenuItem::getId();
    if (i < this->valuesNum) {
        this->saveHandler(i, this->descriptors[i].text, this->descriptors[i].maxLength);
    }
}

void ValueTextManager::cancel(MenuItem &item)
{
    this->load(item);
}

};
