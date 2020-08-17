#include "ProMenuUtils.h"

namespace promenu::utils {

void rightPaddingText(char *text, int length, char ch)
{
    bool pad = false;
    for (int i = 0; i < length; i++) {
        if (pad == false) {
            if (text[i] == 0) {
                pad = true;
                text[i] = ch;
            }
        } else {
            text[i] = (i == length - 1) ? 0 : ch;
        }
    }
}

};
