#ifndef PRO_MENU_ADAPTERS_H
#define PRO_MENU_ADAPTERS_H

#include <LiquidCrystal.h>
#include <SmartButton.h>

#include "ProMenuDefs.h"
#include "ProMenuDisplay.h"
#include "ProMenuManager.h"

#include <stdint.h>

namespace promenu::adapters {

constexpr int LCD_RS = 8, LCD_EN = 9, LCD_D4 = 4, LCD_D5 = 5, LCD_D6 = 6, LCD_D7 = 7;
constexpr int LCD_WIDTH = 16;
constexpr int LCD_HEIGHT = 2;

class LcdShieldDisplay: public promenu::DisplayInterface {

public:
    LcdShieldDisplay(
        int lcdWidth = LCD_WIDTH, int lcdHeight = LCD_HEIGHT,
        int menuWidth = LCD_WIDTH, int menuHeight = LCD_HEIGHT,
        int menuXOffset = 0, int menuYOffset = 0,
        int rs = LCD_RS, int en = LCD_EN, int d4 = LCD_D4, int d5 = LCD_D5, int d6 = LCD_D6, int d7 = LCD_D7
    );

    virtual void setCursor(int x, int y);
    virtual void printText(const char *text);
    virtual void setText(int x, int y, const char *text);
    virtual void setChar(int x, int y, char ch);
    virtual void selectChar(int x, int y);
    virtual void deselectChar();
    virtual void showCursor(int x, int y);
    virtual void hideCursor();
    virtual void clear();
    virtual void begin();
    virtual void end();

    virtual char getArrowUp();
    virtual char getArrowDown();
    virtual char getArrowUpDown();
    
    LiquidCrystal lcd;

private:
    static constexpr char arrowUpChar = 0x01;
    static constexpr char arrowDownChar = 0x02;
    static constexpr char arrowUpDownChar = 0x03;

    const uint8_t arrowUp[8] = {B00100, B01010, B10001, B00000, B00000, B00000, B00000, B00000};
    const uint8_t arrowDown[8] = {B00000, B00000, B00000, B00000, B10001, B01010, B00100, B00000};
    const uint8_t arrowUpDown[8] = {B00100, B01010, B10001, B00000, B10001, B01010, B00100, B00000};

    const int lcdWidth;
    const int lcdHeight;
    const int menuWidth;
    const int menuHeight;
    const int menuXOffset;
    const int menuYOffset;
};

constexpr int BUTTON_ADC_PIN = A0;

constexpr int BUTTON_ADC_ACCEPT_RANGE = 50;

constexpr int BUTTON_UP_ADC_VALUE = 99;
constexpr int BUTTON_DOWN_ADC_VALUE = 255;
constexpr int BUTTON_LEFT_ACS_VALUE = 409;
constexpr int BUTTON_SELECT_ACS_VALUE = 0;

class LcdShieldButtons: smartbutton::SmartButtonInterface {

public:
    LcdShieldButtons(promenu::MenuManager &manager,
        int buttonAdcPin = BUTTON_ADC_PIN,
        int buttonAdcAcceptRange = BUTTON_ADC_ACCEPT_RANGE,
        int buttonUpThreshhold = BUTTON_UP_ADC_VALUE,
        int buttonDownThreshold = BUTTON_DOWN_ADC_VALUE,
        int buttonBackThreshold = BUTTON_LEFT_ACS_VALUE,
        int buttonSelectThreshold = BUTTON_SELECT_ACS_VALUE
    );

    void begin();
    void process();

private:
    bool isValueInRange(int value, int threshold);
    bool isEvent(smartbutton::SmartButton::Event event);

    virtual void event(smartbutton::SmartButton *button, smartbutton::SmartButton::Event event, int clickCounter);
    virtual bool isPressed(smartbutton::SmartButton *button);

    MenuManager &manager;

    smartbutton::SmartButton buttonUp;
    smartbutton::SmartButton buttonDown;
    smartbutton::SmartButton buttonBack;
    smartbutton::SmartButton buttonSelect;

    bool isButtonUpPressed;
    bool isButtonDownPressed;
    bool isButtonBackPressed;
    bool isButtonSelectPressed;
    
    const int buttonAdcPin;
    const int buttonAdcAcceptRange;

    const int buttonUpThreshold;
    const int buttonDownThreshold;
    const int buttonBackThreshold;
    const int buttonSelectThreshold;
};

};

#endif /* PRO_MENU_ADAPTERS_H */
