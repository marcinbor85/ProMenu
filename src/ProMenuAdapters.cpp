#include "ProMenuAdapters.h"

namespace promenu::adapters {

LcdShieldDisplay::LcdShieldDisplay(
    int lcdWidth, int lcdHeight,
    int menuWidth, int menuHeight, int menuXOffset, int menuYOffset,
    int rs, int en, int d4, int d5, int d6, int d7):
    DisplayInterface(menuWidth, menuHeight),
    lcdWidth(lcdWidth), lcdHeight(lcdHeight),
    menuWidth(menuWidth), menuHeight(menuHeight), menuXOffset(menuXOffset), menuYOffset(menuYOffset),
    lcd(rs, en, d4, d5, d6, d7)
{

}

void LcdShieldDisplay::setText(int x, int y, const char *text)
{
    this->setCursor(x, y);
    lcd.print(text);
}

void LcdShieldDisplay::setChar(int x, int y, const char ch)
{
    this->setCursor(x, y);
    lcd.print(ch);
}

void LcdShieldDisplay::setCursor(int x, int y)
{
    lcd.setCursor(x + this->menuXOffset, y + this->menuYOffset);
}

void LcdShieldDisplay::printText(const char *text)
{
    lcd.print(text);
}

void LcdShieldDisplay::printChar(char ch)
{
    lcd.print(ch);
}

void LcdShieldDisplay::selectChar(int x, int y)
{
    this->setCursor(x, y);
    lcd.blink();
}

void LcdShieldDisplay::deselectChar()
{
    lcd.noBlink();
}

void LcdShieldDisplay::showCursor(int x, int y)
{
    this->setCursor(x, y);
    lcd.cursor();
}

void LcdShieldDisplay::hideCursor()
{
    lcd.noCursor();
}

char LcdShieldDisplay::getArrowUp()
{
    return this->arrowUpChar;
}

char LcdShieldDisplay::getArrowDown()
{
    return this->arrowDownChar;
}

char LcdShieldDisplay::getArrowUpDown()
{
    return this->arrowUpDownChar;
}

void LcdShieldDisplay::clear()
{
    char emptyLine[this->menuWidth + 1];
    
    memset(emptyLine, ' ', sizeof(emptyLine));
    emptyLine[this->menuWidth] = 0;

    for (int y = 0; y < this->menuHeight; y++) {
        this->setCursor(0, y);
        lcd.print(emptyLine);
    }

    lcd.noCursor();
    lcd.noBlink();
}

void LcdShieldDisplay::clearLine(int y)
{
    char emptyLine[this->menuWidth + 1];
    
    memset(emptyLine, ' ', sizeof(emptyLine));
    emptyLine[this->menuWidth] = 0;

    this->setCursor(0, y);
    lcd.print(emptyLine);
}

void LcdShieldDisplay::begin()
{
    lcd.begin(this->lcdWidth, this->lcdHeight);
    
    lcd.createChar(this->arrowUpChar, arrowUp);
    lcd.createChar(this->arrowDownChar, arrowDown);
    lcd.createChar(this->arrowUpDownChar, arrowUpDown);
}

void LcdShieldDisplay::end()
{
    this->clear();
}

LcdShieldButtons::LcdShieldButtons(promenu::MenuManagerInterface &interface,
    int buttonAdcPin,
    int buttonAdcAcceptRange,
    int buttonUpThreshhold,
    int buttonDownThreshold,
    int buttonBackThreshold,
    int buttonSelectThreshold
):
    interface(interface),
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
    buttonUp(-1, smartbutton::SmartButton::InputType::NORMAL_HIGH, NULL, NULL, this, 20UL, 500UL, 1000UL, 2000UL, 200UL, 200UL),
    buttonDown(-1, smartbutton::SmartButton::InputType::NORMAL_HIGH, NULL, NULL, this, 20UL, 500UL, 1000UL, 2000UL, 200UL, 200UL),
    buttonBack(-1, smartbutton::SmartButton::InputType::NORMAL_HIGH, NULL, NULL, this, 20UL, 500UL, 1000UL, 2000UL, 200UL, 200UL),
    buttonSelect(-1, smartbutton::SmartButton::InputType::NORMAL_HIGH, NULL, NULL, this, 20UL, 500UL, 1000UL, 2000UL, 200UL, 200UL)
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

bool LcdShieldButtons::isEvent(smartbutton::SmartButton::Event event)
{
    if (event == smartbutton::SmartButton::Event::PRESSED ||
            event == smartbutton::SmartButton::Event::HOLD ||
            event == smartbutton::SmartButton::Event::HOLD_REPEAT ||
            event == smartbutton::SmartButton::Event::LONG_HOLD ||
            event == smartbutton::SmartButton::Event::LONG_HOLD_REPEAT) {
        return true;
    }
    return false;
}

void LcdShieldButtons::event(smartbutton::SmartButton *button, smartbutton::SmartButton::Event event, int clickCounter)
{
    int repeat;

    if (this->isEvent(event) == false)
        return;

    repeat = (button->getState() == smartbutton::SmartButton::State::LONG_HOLD) ? 10 : 1;

    if (button == &this->buttonUp) {
        this->interface.up(repeat);
    } else if (button == &this->buttonDown) {
        this->interface.down(repeat);
    } else if (button == &this->buttonBack) {
        this->interface.back(repeat);
    } else if (button == &this->buttonSelect) {
        this->interface.select(repeat);
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
