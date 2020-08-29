#include <Arduino.h>

#include <ProMenu.h>
#include <ProMenuManager.h>
#include <ProMenuItem.h>
#include <ProMenuItemCheckbox.h>
#include <ProMenuCheckboxManager.h>
#include <ProMenuAdapters.h>

using namespace promenu;
using namespace promenu::adapters;
using namespace promenu::managers;

constexpr int LED_PIN = 13;
constexpr int BACKLIGHT_PIN = 10;

LcdShieldDisplay display{};

MenuManager menuManager(display);

static bool ledState = false;
static bool blinkState = false;
static bool backlightState = true;

static bool* const checkboxValuesPtr[] = {
    &ledState,
    &blinkState,
    &backlightState
};

static bool checkboxTempValues[3];
CheckboxManager checkboxManager(checkboxTempValues, sizeof(checkboxTempValues) / sizeof(checkboxTempValues[0]),
    [](int id, bool *val) {
        *val = *checkboxValuesPtr[id];
    }, [](int id, bool val) {
        *checkboxValuesPtr[id] = val;
    }
);

const MenuItemCheckbox checkboxLed(0, "Led", checkboxManager);
const MenuItemCheckbox checkboxBlink(1, "Blink", checkboxManager);
const MenuItemCheckbox checkboxBacklight(2, "Backlight", checkboxManager);

const MenuItem *menuItems[] = {&checkboxLed, &checkboxBlink, &checkboxBacklight};
Menu menu(0, "menu", menuItems, sizeof(menuItems) / sizeof(menuItems[0]));

LcdShieldButtons buttons(menuManager);

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BACKLIGHT_PIN, OUTPUT);

    menuManager.begin(menu); 
    buttons.begin();
}

void loop()
{
    static long blinkLastTick = 0;

    if (blinkState) {
        if (millis() - blinkLastTick >= 500UL) {
            blinkLastTick = millis();
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        }
    } else {
        digitalWrite(LED_PIN, ledState);
    }

    digitalWrite(BACKLIGHT_PIN, backlightState);

    menuManager.process();
    buttons.process();
}

