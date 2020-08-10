#ifndef PRO_MENU_ADAPTERS_H
#define PRO_MENU_ADAPTERS_H

#include <LiquidCrystal.h>
#include <SmartButton.h>

#include "ProMenu.h"
#include "ProMenuDisplay.h"

namespace promenu::adapters {

constexpr int LCD_RS = 8, LCD_EN = 9, LCD_D4 = 4, LCD_D5 = 5, LCD_D6 = 6, LCD_D7 = 7;
constexpr int LCD_WIDTH = 16;
constexpr int LCD_HEIGHT = 2;

class DisplayLiquidCrystal: public promenu::DisplayInterface {

public:
    
    DisplayLiquidCrystal(
        int width = LCD_WIDTH, int height = LCD_HEIGHT,
        int rs = LCD_RS, int en = LCD_EN, int d4 = LCD_D4, int d5 = LCD_D5, int d6 = LCD_D6, int d7 = LCD_D7
    ):
        DisplayInterface(width, height),
        lcd(rs, en, d4, d5, d6, d7) {};

    virtual void setText(int x, int y, const char *text) {
        lcd.setCursor(x, y);
        lcd.print(text);
    }

    virtual void clear() {
        lcd.clear();
    }

    virtual void begin() {
        lcd.begin(promenu::DisplayInterface::getWidth(), promenu::DisplayInterface::getHeight());
        
        lcd.createChar(0x01, arrowUp);
        lcd.createChar(0x02, arrowDown);
    }
    
    LiquidCrystal lcd;

private:
    const byte arrowUp[8] = {
        B00100,
        B01110,
        B10101,
        B00100,
        B00100,
        B00100,
        B00100,
        B00000,
    };
    const byte arrowDown[8] = {
        B00100,
        B00100,
        B00100,
        B00100,
        B10101,
        B01110,
        B00100,
        B00000,
    };
};

constexpr int BUTTON_PIN = A0;

constexpr int BUTTON_ADC_ACCEPT_RANGE = 50;

constexpr int BUTTON_UP_ADC_VALUE = 99;
constexpr int BUTTON_DOWN_ADC_VALUE = 255;
constexpr int BUTTON_LEFT_ACS_VALUE = 409;
constexpr int BUTTON_SELECT_ACS_VALUE = 0;

class LcdShieldButtons: smartbutton::SmartButtonInterface {

public:
    LcdShieldButtons(promenu::MenuManager &manager,
        int buttonPin = BUTTON_PIN,
        int buttonAdcAcceptRange = BUTTON_ADC_ACCEPT_RANGE,
        int buttonUpThreshhold = BUTTON_UP_ADC_VALUE,
        int buttonDownThreshold = BUTTON_DOWN_ADC_VALUE,
        int buttonBackThreshold = BUTTON_LEFT_ACS_VALUE,
        int buttonSelectThreshold = BUTTON_SELECT_ACS_VALUE
    ):
        manager(manager),
        buttonPin(buttonPin),
        buttonAdcAcceptRange(buttonAdcAcceptRange),
        buttonUpThreshold(buttonUpThreshhold),
        buttonDownThreshold(buttonDownThreshold),
        buttonBackThreshold(buttonBackThreshold),
        buttonSelectThreshold(buttonSelectThreshold),
        isButtonUpPressed(false),
        isButtonDownPressed(false),
        isButtonBackPressed(false),
        isButtonSelectPressed(false),
        buttonUp(this),
        buttonDown(this),
        buttonBack(this),
        buttonSelect(this) {};

    void begin() {
        pinMode(this->buttonPin, INPUT);

        this->buttonUp.begin();
        this->buttonDown.begin();
        this->buttonBack.begin();
        this->buttonSelect.begin();
    }

    void process() {
        int val;

        val = analogRead(this->buttonPin);

        this->isButtonUpPressed = false;
        this->isButtonDownPressed = false;
        this->isButtonBackPressed = false;
        this->isButtonSelectPressed = false;
        
        if (this->isValueInRange(val, this->buttonUpThreshold) != false) {
            this->isButtonUpPressed = true;
        } else if (this->isValueInRange(val, this->buttonDownThreshold) != false) {
            this->isButtonDownPressed = true;
        } else if (this->isValueInRange(val, this->buttonBackThreshold) != false) {
            this->isButtonBackPressed = true;
        } else if (this->isValueInRange(val, this->buttonSelectThreshold) != false) {
            this->isButtonSelectPressed = true;
        }

        this->buttonUp.process();
        this->buttonDown.process();
        this->buttonBack.process();
        this->buttonSelect.process();
    }

private:
    bool isValueInRange(int value, int threshold) {
        if ((value > threshold - buttonAdcAcceptRange) && (value < threshold + buttonAdcAcceptRange)) {
            return true;
        } else {
            return false;
        }
    };

    virtual void event(smartbutton::SmartButton *button, smartbutton::SmartButton::Event event, int clickCounter)
    {
        if (button == &this->buttonUp) {
            if (event == smartbutton::SmartButton::Event::PRESSED) {
                this->manager.up();
            }
        } else if (button == &this->buttonDown) {
            if (event == smartbutton::SmartButton::Event::PRESSED) {
                this->manager.down();
            }
        } else if (button == &this->buttonBack) {
            if (event == smartbutton::SmartButton::Event::PRESSED) {
                this->manager.back();
            }
        } else if (button == &this->buttonSelect) {
            if (event == smartbutton::SmartButton::Event::PRESSED) {
                this->manager.select();
            }
        }
    }

    virtual bool isPressed(smartbutton::SmartButton *button)
    {
        if (button == &this->buttonUp) {
            return this->isButtonUpPressed;
        } else if (button == &this->buttonDown) {
            return this->isButtonDownPressed;
        } else if (button == &this->buttonBack) {
            return this->isButtonBackPressed;
        } else if (button == &this->buttonSelect) {
            return this->isButtonSelectPressed;
        } else {
            return false;
        }
    }

    MenuManager &manager;

    smartbutton::SmartButton buttonUp;
    smartbutton::SmartButton buttonDown;
    smartbutton::SmartButton buttonBack;
    smartbutton::SmartButton buttonSelect;

    bool isButtonUpPressed;
    bool isButtonDownPressed;
    bool isButtonBackPressed;
    bool isButtonSelectPressed;
    
    const int buttonPin;
    const int buttonAdcAcceptRange;

    const int buttonUpThreshold;
    const int buttonDownThreshold;
    const int buttonBackThreshold;
    const int buttonSelectThreshold;
};

};

#endif /* PRO_MENU_ADAPTERS_H */
