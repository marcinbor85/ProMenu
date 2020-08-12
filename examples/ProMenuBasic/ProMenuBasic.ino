#include <Arduino.h>

#include <ProMenu.h>
#include <ProMenuManager.h>
#include <ProMenuItem.h>
#include <ProMenuItemCheckbox.h>
#include <ProMenuItemSubmenu.h>
#include <ProMenuItemAction.h>
#include <ProMenuItemValue.h>
#include <ProMenuAdapters.h>

using namespace promenu;
using namespace promenu::adapters;

constexpr int LED_PIN = 13;
constexpr int BACKLIGHT_PIN = 10;

LcdShieldDisplay display{};

MenuManager menuManager(display);

class CheckboxManager: public MenuItemCheckboxInterface {
public:
    virtual bool isSelected(MenuItemCheckbox &item)
    {
        int i = item.getId();
        return this->value[i];
    }
    virtual void setSelected(MenuItemCheckbox &item, bool val)
    {
        int i = item.getId();
        this->value[i] = val;
    }
    bool value[2];
};

CheckboxManager checkboxManager;

class ActionManager: public MenuItemActionInterface {
public:
    virtual void action(MenuItemAction &item)
    {
        switch (item.getId()) {
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
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
        }
    }
};

ActionManager actionManager;


template <class T>
class ValueManager: public MenuItemValueInterface<T> {

public:
    virtual void init(MenuItemValue<T> &item)
    {
        int i = item.MenuItem::getId();
        this->tempValue[i] = this->currentValue[i];
    }
    virtual T getMin(MenuItemValue<T> &item)
    {
        switch (item.MenuItem::getId()) {
        case 0:
            return 0;
        }
        return 0;
    }
    virtual T getMax(MenuItemValue<T> &item)
    {
        switch (item.MenuItem::getId()) {
        case 0:
            return 10;
        }
        return 0;
    }
    virtual void setValue(MenuItemValue<T> &item, T value)
    {
        int i = item.MenuItem::getId();
        this->tempValue[i]= value;
    }
    virtual T getValue(MenuItemValue<T> &item)
    {
        int i = item.MenuItem::getId();
        return this->tempValue[i];
    }
    virtual bool save(MenuItemValue<T> &item)
    {
        int i = item.MenuItem::getId();
        this->currentValue[i] = this->tempValue[i];
        return true;
    }
    virtual void cancel(MenuItemValue<T> &item)
    {
        this->init(item);
    }

    T tempValue[1];
    T currentValue[1];
};

ValueManager<int> valueIntManager;


const MenuItemAction action31(10, "Enable", actionManager);
const MenuItemAction action32(11, "Disable", actionManager);
const MenuItemCheckbox checkbox1(0, "Feature1", checkboxManager);
const MenuItemCheckbox checkbox2(1, "Feature2", checkboxManager);

const MenuItem *menuMisc2Items[] = {&action31, &action32, &checkbox1, &checkbox2};
Menu menuMisc2(1, "misc3", menuMisc2Items, sizeof(menuMisc2Items) / sizeof(menuMisc2Items[0]));


const MenuItemAction action21(12, "Toggle", actionManager);
const MenuItemValue<int> number1(0, "Value", valueIntManager);

const MenuItem *menuMiscItems[] = {&action21, &number1};
Menu menuMisc(1, "misc", menuMiscItems, sizeof(menuMiscItems) / sizeof(menuMiscItems[0]));


const MenuItemAction action11(20, "Led OFF", actionManager);
const MenuItemAction action12(21, "Led ON", actionManager);
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

    menuManager.begin(&menuRoot); 
    buttons.begin();
}

void loop()
{
    menuManager.process();
    buttons.process();
}

