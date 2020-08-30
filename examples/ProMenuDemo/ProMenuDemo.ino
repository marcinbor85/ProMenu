#include <Arduino.h>

#include <ProMenu.h>
#include <ProMenuManager.h>
#include <ProMenuItem.h>
#include <ProMenuItemEdit.h>
#include <ProMenuItemCheckbox.h>
#include <ProMenuCheckboxManager.h>
#include <ProMenuValueNumberManager.h>
#include <ProMenuValueEnumManager.h>
#include <ProMenuValueTextManager.h>
#include <ProMenuActionManager.h>
#include <ProMenuItemSubmenu.h>
#include <ProMenuItemAction.h>
#include <ProMenuItemValue.h>
#include <ProMenuItemText.h>
#include <ProMenuAdapters.h>

using namespace promenu;
using namespace promenu::adapters;
using namespace promenu::managers;

constexpr int LED_PIN = 13;
constexpr int BACKLIGHT_PIN = 10;

LcdShieldDisplay display{16, 2, 14, 1, 1, 1};
//LcdShieldDisplay display{};

MenuManager menuManager(display);

static bool checkboxTempValues[2];
static bool checkboxExternalValues[2] = {false, true};
CheckboxManager checkboxManager(checkboxTempValues, sizeof(checkboxTempValues) / sizeof(checkboxTempValues[0]),
    [](int id, bool *val) {
        *val = checkboxExternalValues[id];
    }, [](int id, bool val) {
        checkboxExternalValues[id] = val;
    }
);

ActionManager actionManager([](int id) -> bool {
    switch (id) {
        case 0:
            return false;
        case 1:
            return false;
        case 2:
            void (*resetFunc) (void) = 0;
            delay(500);
            resetFunc();
            break;
        default:
            return false;
        }
    return true;
});

static long longTempValues[3];
static long longExternalValues[3] = {-50, 1, -500};
struct ValueNumberManager::NumberDescriptor valuesDesc[3] = {
    {
        .min = -100,
        .max = 100,
        .decimalPlaces = 1,
        .step = 1,
        .value = &longTempValues[0]
    },
    {
        .min = 0,
        .max = 100,
        .decimalPlaces = 0,
        .step = 1,
        .value = &longTempValues[1]
    },
    {
        .min = -1000,
        .max = 1000,
        .decimalPlaces = 3,
        .step = 1,
        .value = &longTempValues[2]
    }
};

ValueNumberManager valueLongManager(valuesDesc, sizeof(valuesDesc)/sizeof(valuesDesc[0]),
    [](int id, long *val) {
        *val = longExternalValues[id];
    }, [](int id, long val) {
        longExternalValues[id] = val;
    }
);

static const char *speedEnum[3] = {"LOW", "MID", "HIGH"};
static const char *stateEnum[2] = {"OFF", "ON"};

static int enumTempValues[2];
static int enumExternalValues[2] = {0, 0};
struct ValueEnumManager::EnumDescriptor enumsDesc[2] = {
    {
        .enumText = speedEnum,
        .enumSize = sizeof(speedEnum)/sizeof(speedEnum[0]),
        .value = &enumTempValues[0],
    },
    {
        .enumText = stateEnum,
        .enumSize = sizeof(stateEnum)/sizeof(stateEnum[0]),
        .value = &enumTempValues[1],
    }
};

ValueEnumManager valueEnumManager(enumsDesc, sizeof(enumsDesc)/sizeof(enumsDesc[0]),
    [](int id, int *val) {
        *val = enumExternalValues[id];
    }, [](int id, int val) {
        enumExternalValues[id] = val;
    }
);

static char textTempValues1[20];
static char textTempValues2[5];

static char textExternalValues1[] = {"Embedded Devices"};
static char textExternalValues2[] = {"Test"};

struct ValueTextManager::TextDescriptor textDesc[2] = {
    {
        .text = textTempValues1,
        .maxLength = sizeof(textTempValues1)
    },
    {
        .text = textTempValues2,
        .maxLength = sizeof(textTempValues2)
    }
};
ValueTextManager valueTextManager(textDesc, sizeof(textDesc)/sizeof(textDesc[0]),
    [](int id, char *text, int maxLength) {
        switch (id) {
        case 0:
            strcpy(text, textExternalValues1);
            break;
        case 1:
            strcpy(text, textExternalValues2);
            break;
        default:
            if (maxLength > 0)
                text[0] = 0;
        }
    }, [](int id, char *text, int maxLength) {
        switch (id) {
        case 0:
            memcpy(textExternalValues1, text, maxLength);
            break;
        case 1:
            memcpy(textExternalValues2, text, maxLength);
            break;
        }
    }
);


const MenuItemText string1(0, "Title", valueTextManager);
const MenuItemText string2(1, "Password", valueTextManager);

const MenuItem *menuTextItems[] = {&string1, &string2};
Menu menuText("Text", menuTextItems, sizeof(menuTextItems) / sizeof(menuTextItems[0]));


const MenuItemValue enum1(0, "Speed", valueEnumManager);
const MenuItemValue enum2(1, "Blinking", valueEnumManager);

const MenuItem *menuEnumerationItems[] = {&enum1, &enum2};
Menu menuEnumeration("Enumeration", menuEnumerationItems, sizeof(menuEnumerationItems) / sizeof(menuEnumerationItems[0]));


const MenuItemValue number1(0, "Signed", valueLongManager);
const MenuItemValue number2(1, "Unsigned", valueLongManager);
const MenuItemValue number3(2, "Float", valueLongManager);

const MenuItem *menuNumberItems[] = {&number1, &number2, &number3};
Menu menuNumber("Number", menuNumberItems, sizeof(menuNumberItems) / sizeof(menuNumberItems[0]));


const MenuItemCheckbox checkbox1(0, "Led", checkboxManager);
const MenuItemCheckbox checkbox2(1, "Backlight", checkboxManager);

const MenuItem *menuBooleanItems[] = {&checkbox1, &checkbox2};
Menu menuBoolean("Boolean", menuBooleanItems, sizeof(menuBooleanItems) / sizeof(menuBooleanItems[0]));


const MenuItemSubmenu valuesBoolean(0, "Boolean", menuBoolean);
const MenuItemSubmenu valuesNumber(1, "Number", menuNumber);
const MenuItemSubmenu valuesEnumeration(2, "Enumeration", menuEnumeration);
const MenuItemSubmenu valuesText(3, "Text", menuText);

const MenuItem *menuValuesItems[] = {&valuesBoolean, &valuesNumber, &valuesEnumeration, &valuesText};
Menu menuValues("Values", menuValuesItems, sizeof(menuValuesItems) / sizeof(menuValuesItems[0]));


const MenuItemAction action1(0, "Fire", actionManager);
const MenuItemAction action2(1, "Release", actionManager);
const MenuItemAction action3(2, "Reset (reboot system)", actionManager);

const MenuItem *menuActionsItems[] = {&action1, &action2, &action3};
Menu menuActions("Actions", menuActionsItems, sizeof(menuActionsItems) / sizeof(menuActionsItems[0]));


const MenuItemSubmenu menuActionsItemSubmenu(0, "Actions", menuActions);
const MenuItemSubmenu menuValuesItemSubmenu(1, "Values", menuValues);

const MenuItem *rootItems[] = {&menuActionsItemSubmenu, &menuValuesItemSubmenu};
Menu menuRoot("Root", rootItems, sizeof(rootItems) / sizeof(rootItems[0]));


LcdShieldButtons buttons(menuManager);

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BACKLIGHT_PIN, OUTPUT);

    menuManager.begin(menuRoot); 
    buttons.begin();
}

void loop()
{
    static unsigned long blinkLastTick = 0;
    unsigned long period;

    if (enumExternalValues[1] != 0) {
        switch (enumExternalValues[0]) {
        case 0:
            period = 1000UL;
            break;
        case 1:
            period = 500UL;
            break;
        case 2:
            period = 100UL;
            break;
        }
        if (millis() - blinkLastTick > period) {
            blinkLastTick = millis();
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        }
    } else {
        digitalWrite(LED_PIN, checkboxExternalValues[0]);
    }

    digitalWrite(BACKLIGHT_PIN, checkboxExternalValues[1]);

    menuManager.process();
    buttons.process();
}

