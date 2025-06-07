#include "LcdHelper.h"

LcdHelper *LcdHelper::instance = nullptr;

LcdHelper *LcdHelper::get()
{
    if (LcdHelper::instance == nullptr)
    {
        instance = new LcdHelper();
    }

    return instance;
}

LcdHelper::LcdHelper()
{
    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
}

void LcdHelper::init()
{
    lcd->init();

    uint8_t charmap0[8] = {0x00, 0x00, 0x0A, 0x00, 0x11, 0x0E, 0x00, 0x00};
    uint8_t charmap1[8] = {0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E};
    uint8_t charmap2[8] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E};
    uint8_t charmap3[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    uint8_t charmap4[8] = {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
    uint8_t charmap5[8] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
    uint8_t charmap6[8] = {0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c};
    uint8_t charmap7[8] = {0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e};

    lcd->createChar(0, charmap0);
    lcd->createChar(1, charmap1);
    lcd->createChar(2, charmap2);
    lcd->createChar(3, charmap3);
    lcd->createChar(4, charmap4);
    lcd->createChar(5, charmap5);
    lcd->createChar(6, charmap6);
    lcd->createChar(7, charmap7);
}

void LcdHelper::turnoffBacklight()
{
    lcd->setBacklight(0);
}

void LcdHelper::animFadeIn()
{
    for (int x = 0; x < 16; x++)
    {
        lcd->setCursor(x, 0);
        lcd->write(3);
        lcd->setCursor(x, 1);
        lcd->write(3);

        lcd->setCursor(x, 0);
        lcd->write(4);
        lcd->setCursor(x, 1);
        lcd->write(4);

        lcd->setCursor(x, 0);
        lcd->write(5);
        lcd->setCursor(x, 1);
        lcd->write(5);

        lcd->setCursor(x, 0);
        lcd->write(6);
        lcd->setCursor(x, 1);
        lcd->write(6);

        lcd->setCursor(x, 0);
        lcd->write(7);
        lcd->setCursor(x, 1);
        lcd->write(7);
    }
}

void LcdHelper::animFadeOut()
{
    for (int x = 15; x >= 0; x--)
    {
        lcd->setCursor(x, 0);
        lcd->write(7);
        lcd->setCursor(x, 1);
        lcd->write(7);

        lcd->setCursor(x, 0);
        lcd->write(6);
        lcd->setCursor(x, 1);
        lcd->write(6);

        lcd->setCursor(x, 0);
        lcd->write(5);
        lcd->setCursor(x, 1);
        lcd->write(5);

        lcd->setCursor(x, 0);
        lcd->write(4);
        lcd->setCursor(x, 1);
        lcd->write(4);

        lcd->setCursor(x, 0);
        lcd->write(3);
        lcd->setCursor(x, 1);
        lcd->write(3);

        lcd->setCursor(x, 0);
        lcd->print(' ');
        lcd->setCursor(x, 1);
        lcd->print(' ');
    }
}

void LcdHelper::setCursor(uint8_t onoff, uint8_t blink)
{
    if (onoff)
    {
        lcd->cursor_on();
    }
    else
    {
        lcd->cursor_off();
    }

    if (blink)
    {
        lcd->blink_on();
    }
    else
    {
        lcd->blink_off();
    }
}

void LcdHelper::setPosition(uint8_t x, uint8_t y)
{
    lcd->setCursor(x, y);
}

void LcdHelper::print(const char *str)
{
    lcd->print(str);
}

void LcdHelper::clear()
{
    lcd->clear();
}

void LcdHelper::print(char ch)
{
    lcd->print(ch);
}

LiquidCrystal_I2C *LcdHelper::device()
{
    return lcd;
}

void LcdHelper::setBacklight(bool onOff)
{
    lcd->setBacklight(onOff ? 1 : 0);
}