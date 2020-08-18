#include <Arduino.h>

#include <ProMenu.h>
#include <ProMenuManager.h>
#include <ProMenuItem.h>
#include <ProMenuItemEdit.h>
#include <ProMenuItemCheckbox.h>
#include <ProMenuCheckboxManager.h>
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

static bool checkboxValues[2];
CheckboxManager checkboxManager(checkboxValues, sizeof(checkboxValues) / sizeof(checkboxValues[0]));

ActionManager actionManager([](int id) -> bool {
    switch (id) {
        case 10:
            return false;
        case 11:
            return false;
        case 12:
            return false;
        case 13:
            return false;
        case 20:
            digitalWrite(LED_PIN, LOW);
            break;
        case 21:
            digitalWrite(LED_PIN, HIGH);
            break;
        case 22:
            digitalWrite(BACKLIGHT_PIN, LOW);
            break;
        case 23:
            digitalWrite(BACKLIGHT_PIN, HIGH);
            break;
        default:
            return false;
        }
    return true;
});

class ValueLongManager: public MenuItemValueInterface {

public:
    ValueLongManager():
        minMaxValue({{-100,100}, {0, 100}}) {};

    virtual void init(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        this->tempValue[i] = this->currentValue[i];
    }
    virtual bool prevValue(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        if (this->tempValue[i] > this->minMaxValue[i][0]) {
            this->tempValue[i]--;
            return true;
        }
        return false;
    }
    virtual bool nextValue(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        if (this->tempValue[i] < this->minMaxValue[i][1]) {
            this->tempValue[i]++;
            return true;
        }
        return false;
    }
    virtual void getValueText(MenuItemEdit &item, char *text, int maxSize)
    {
        int i = item.MenuItem::getId();
        snprintf(text, maxSize, "%ld", this->tempValue[i]);
    }
    virtual void save(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        this->currentValue[i] = this->tempValue[i];
    }
    virtual void cancel(MenuItemEdit &item)
    {
        this->init(item);
    }
    virtual bool isPrevValueAvailable(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        return (this->tempValue[i] > this->minMaxValue[i][0]);
    }
    virtual bool isNextValueAvailable(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        return (this->tempValue[i] < this->minMaxValue[i][1]);
    }

    long tempValue[2];
    long currentValue[2];

    const long minMaxValue[2][2];
};

ValueLongManager valueLongManager;

class ValueTriStateManager: public MenuItemValueInterface {

public:
    ValueTriStateManager():
        valueNames({"LOW", "MID", "HIGH"}),
        valueNamesNum((sizeof(this->valueNames) / sizeof(this->valueNames[0]))) {};

    virtual void init(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        this->tempValue[i] = this->currentValue[i];
    }
    virtual bool prevValue(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        if (this->tempValue[i] > 0) {
            this->tempValue[i]--;
            return true;
        }
        return false;
    }
    virtual bool nextValue(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        if (this->tempValue[i] < valueNamesNum - 1) {
            this->tempValue[i]++;
            return true;
        }
        return false;
    }
    virtual void getValueText(MenuItemEdit &item, char *text, int maxSize)
    {
        int i = item.MenuItem::getId();
        snprintf(text, maxSize, "%s", this->valueNames[this->tempValue[i]]);
    }
    virtual void save(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        this->currentValue[i] = this->tempValue[i];
    }
    virtual void cancel(MenuItemEdit &item)
    {
        this->init(item);
    }
    virtual bool isPrevValueAvailable(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        return (this->tempValue[i] > 0);
    }
    virtual bool isNextValueAvailable(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        return (this->tempValue[i] < valueNamesNum - 1);
    }

    int tempValue[1];
    int currentValue[1];

    const char *valueNames[3];
    const int valueNamesNum;
};

ValueTriStateManager valueTriStateManager;

class ValueStringManager: public MenuItemTextInterface {

public:
    static constexpr int maxTextSize = 30;

    ValueStringManager():
        currentText{{"Test Embedded Devices"}, {"Krotki"}} {}

    virtual void init(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        memcpy(this->tempText[i], this->currentText[i], maxTextSize);
    }
    virtual void setChar(MenuItemEdit &item, int p, char ch)
    {
        int i = item.MenuItem::getId();
        if (p < maxTextSize)
            this->tempText[i][p] = ch;
    }
    virtual char getChar(MenuItemEdit &item, int p)
    {
        int i = item.MenuItem::getId();
        if (p < maxTextSize)
            return this->tempText[i][p];
        return 0;
    }
    virtual void save(MenuItemEdit &item)
    {
        int i = item.MenuItem::getId();
        memcpy(this->currentText[i], this->tempText[i], maxTextSize);
    }
    virtual void cancel(MenuItemEdit &item)
    {
        this->init(item);
    }

    char currentText[2][maxTextSize];
    char tempText[2][maxTextSize];
};

ValueStringManager valueStringManager;

const MenuItemAction action31(10, "Enable", actionManager);
const MenuItemAction action32(11, "Disable", actionManager);
const MenuItemCheckbox checkbox1(0, "Feature1 long", checkboxManager);
const MenuItemCheckbox checkbox2(1, "Feature2", checkboxManager);

const MenuItem *menuMisc2Items[] = {&action31, &action32, &checkbox1, &checkbox2};
Menu menuMisc2(1, "misc3", menuMisc2Items, sizeof(menuMisc2Items) / sizeof(menuMisc2Items[0]));


const MenuItemValue triState1(0, "State Machine", valueTriStateManager);
const MenuItemValue number1(0, "ValueS test1 test2 test3", valueLongManager);
const MenuItemValue number2(1, "ValueU", valueLongManager);
const MenuItemText string1(0, "String", valueStringManager);
const MenuItemText string2(1, "String very very long", valueStringManager);

const MenuItem *menuMiscItems[] = {&triState1, &number1, &number2, &string1, &string2};
Menu menuMisc(1, "misc", menuMiscItems, sizeof(menuMiscItems) / sizeof(menuMiscItems[0]));


const MenuItemAction action11(20, "--- Led OFF +++ test test", actionManager);
const MenuItemAction action12(21, "Led ON aabbccdd eeff gg hhh", actionManager);
const MenuItemAction action13(22, "Light OFF", actionManager);
const MenuItemAction action14(23, "Light ON", actionManager);

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

