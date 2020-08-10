#include <Arduino.h>

#include <ProMenu.h>
#include <ProMenuManager.h>
#include <ProMenuItem.h>
#include <ProMenuItemAction.h>
#include <ProMenuItemSubmenu.h>
#include <ProMenuAdapters.h>

using namespace promenu;
using namespace promenu::adapters;

constexpr int LED_PIN = 13;
constexpr int BACKLIGHT_PIN = 10;

DisplayLiquidCrystal display{};

MenuManager menuManager(display);

const MenuItemAction action11(11, "Led OFF", [](MenuItem *item, MenuManager *manager) {
    digitalWrite(LED_PIN, LOW);
    return 0;
});

const MenuItemAction action12(12, "Led ON", [](MenuItem *item, MenuManager *manager) {
    digitalWrite(LED_PIN, HIGH);
    return 0;
});

const MenuItemAction action13(13, "Light OFF", [](MenuItem *item, MenuManager *manager) {
    digitalWrite(BACKLIGHT_PIN, LOW);
    return 0;
});

const MenuItemAction action14(14, "Light ON", [](MenuItem *item, MenuManager *manager) {
    digitalWrite(BACKLIGHT_PIN, HIGH);
    return 0;
});

const MenuItem *menuActionItems[] = {
    &action11, &action12, &action13, &action14
};

Menu menuAction(1, "actions", menuActionItems, 4);

const MenuItemSubmenu menuActionItemSubmenu(1, "Actions", menuAction);

const MenuItem *rootItems[] = {
    &menuActionItemSubmenu
};

Menu menuRoot(1, "root", rootItems, 1);

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

