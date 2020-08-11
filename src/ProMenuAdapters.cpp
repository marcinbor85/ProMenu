#include "ProMenuAdapters.h"

namespace promenu::adapters {

LcdShieldDisplay::LcdShieldDisplay(int width, int height, int rs, int en, int d4, int d5, int d6, int d7):
    DisplayInterface(width, height),
    lcd(rs, en, d4, d5, d6, d7)
{

}

void LcdShieldDisplay::setText(int x, int y, const char *text)
{
    lcd.setCursor(x, y);
    lcd.print(text);
}

void LcdShieldDisplay::clear()
{
    lcd.clear();
}

void LcdShieldDisplay::begin()
{
    lcd.begin(promenu::DisplayInterface::getWidth(), promenu::DisplayInterface::getHeight());
    
    lcd.createChar(0x01, arrowUp);
    lcd.createChar(0x02, arrowDown);
}

void LcdShieldDisplay::end()
{
    lcd.clear();
}

LcdShieldButtons::LcdShieldButtons(promenu::MenuManager &manager,
    int buttonAdcPin,
    int buttonAdcAcceptRange,
    int buttonUpThreshhold,
    int buttonDownThreshold,
    int buttonBackThreshold,
    int buttonSelectThreshold
):
    manager(manager),
    buttonAdcPin(buttonAdcPin),
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
    buttonSelect(this)
{

}

void LcdShieldButtons::begin()
{
    this->buttonUp.begin();
    this->buttonDown.begin();
    this->buttonBack.begin();
    this->buttonSelect.begin();
}

void LcdShieldButtons::process()
{
    int val;

    val = getAdcValue(this->buttonAdcPin);

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

bool LcdShieldButtons::isValueInRange(int value, int threshold)
{
    if ((value > threshold - buttonAdcAcceptRange) && (value < threshold + buttonAdcAcceptRange)) {
        return true;
    } else {
        return false;
    }
};

void LcdShieldButtons::event(smartbutton::SmartButton *button, smartbutton::SmartButton::Event event, int clickCounter)
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

bool LcdShieldButtons::isPressed(smartbutton::SmartButton *button)
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

};
