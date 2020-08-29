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

// LcdShieldDisplay display{16, 2, 14, 1, 1, 1};
LcdShieldDisplay display{};

MenuManager menuManager(display);

static bool checkboxTempValues[2];
static bool checkboxExternalValues[2] = {true, false};
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
            return false;
        case 3:
            return false;
        case 4:
            digitalWrite(LED_PIN, LOW);
            break;
        case 5:
            digitalWrite(LED_PIN, HIGH);
            break;
        case 6:
            digitalWrite(BACKLIGHT_PIN, LOW);
            break;
        case 7:
            digitalWrite(BACKLIGHT_PIN, HIGH);
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
        .min = -1,
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

static const char *triStateEnum[3] = {"LOW", "MID", "HIGH"};
static const char *offOnEnum[2] = {"OFF", "ON"};

static int enumTempValues[2];
static int enumExternalValues[2];
struct ValueEnumManager::EnumDescriptor enumsDesc[2] = {
    {
        .enumText = triStateEnum,
        .enumSize = sizeof(triStateEnum)/sizeof(triStateEnum[0]),
        .value = &enumTempValues[0],
    },
    {
        .enumText = offOnEnum,
        .enumSize = sizeof(offOnEnum)/sizeof(offOnEnum[0]),
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

const MenuItemAction action31(0, "Enable", actionManager);
const MenuItemAction action32(1, "Disable", actionManager);
const MenuItemCheckbox checkbox1(0, "Feature1 long", checkboxManager);
const MenuItemCheckbox checkbox2(1, "Feature2", checkboxManager);

const MenuItem *menuMisc2Items[] = {&action31, &action32, &checkbox1, &checkbox2};
Menu menuMisc2(1, "misc3", menuMisc2Items, sizeof(menuMisc2Items) / sizeof(menuMisc2Items[0]));


const MenuItemValue enum1(0, "State Machine", valueEnumManager);
const MenuItemValue enum2(1, "Functional", valueEnumManager);
const MenuItemValue number1(0, "ValueS test1 test2 test3", valueLongManager);
const MenuItemValue number2(1, "ValueU", valueLongManager);
const MenuItemValue number3(2, "ValueF", valueLongManager);
const MenuItemText string1(0, "String", valueTextManager);
const MenuItemText string2(1, "String very very long", valueTextManager);

const MenuItem *menuMiscItems[] = {&enum1, &enum2, &number1, &number2, &number3, &string1, &string2};
Menu menuMisc(1, "misc", menuMiscItems, sizeof(menuMiscItems) / sizeof(menuMiscItems[0]));


const MenuItemAction action11(4, "--- Led OFF +++ test test", actionManager);
const MenuItemAction action12(5, "Led ON aabbccdd eeff gg hhh", actionManager);
const MenuItemAction action13(6, "Light OFF", actionManager);
const MenuItemAction action14(7, "Light ON", actionManager);

const MenuItem *menuActionItems[] = {&action11, &action12, &action13, &action14};
Menu menuAction(1, "actions", menuActionItems, sizeof(menuActionItems) / sizeof(menuActionItems[0]));


const MenuItemSubmenu menuActionItemSubmenu(1, "Actions", menuAction);
const MenuItemSubmenu menuMiscItemSubmenu(2, "Misc", menuMisc);
const MenuItemSubmenu menuMisc2ItemSubmenu(3, "Misc2", menuMisc2);

const MenuItem *rootItems[] = {&menuActionItemSubmenu, &menuMiscItemSubmenu, &menuMisc2ItemSubmenu};
Menu menuRoot(1, "root", rootItems, sizeof(rootItems) / sizeof(rootItems[0]));


LcdShieldButtons buttons(menuManager);

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    pinMode(BACKLIGHT_PIN, OUTPUT);
    digitalWrite(BACKLIGHT_PIN, HIGH);

    menuManager.begin(menuRoot); 
    buttons.begin();
}

void loop()
{
    menuManager.process();
    buttons.process();
}

