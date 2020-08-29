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
static bool backlightState = true;

constexpr int LED_STATE_ID = 0x00;
constexpr int BACKLIGHT_STATE_ID = 0x01;

static bool checkboxTempValues[2];
CheckboxManager checkboxManager(checkboxTempValues, sizeof(checkboxTempValues) / sizeof(checkboxTempValues[0]),
    [](int id, bool *val) {
        switch (id) {
        case LED_STATE_ID:
            *val = ledState;
            break;
        case BACKLIGHT_STATE_ID:
            *val = backlightState;
            break;
        }
    }, [](int id, bool val) {
        switch (id) {
        case LED_STATE_ID:
            ledState = val;
            break;
        case BACKLIGHT_STATE_ID:
            backlightState = val;
            break;
        }
    }
);

const MenuItemCheckbox checkboxLed(LED_STATE_ID, "Led", checkboxManager);
const MenuItemCheckbox checkboxBacklight(BACKLIGHT_STATE_ID, "Backlight", checkboxManager);

const MenuItem *menuItems[] = {&checkboxLed, &checkboxBacklight};
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
    digitalWrite(LED_PIN, ledState);
    digitalWrite(BACKLIGHT_PIN, backlightState);

    menuManager.process();
    buttons.process();
}

