#ifndef PRO_MENU_DEFS_H
#define PRO_MENU_DEFS_H

#include <Arduino.h>

namespace promenu {

constexpr unsigned long (*getTickValue)() = millis;
constexpr bool (*getGpioState)(int) = digitalRead;
constexpr int (*getAdcValue)(int) = analogRead;

};

#endif /* PRO_MENU_DEFS_H */
