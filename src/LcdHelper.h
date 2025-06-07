#ifndef _LCDHELPER_H_
#define _LCDHELPER_H_

#include <LiquidCrystal_I2C.h>

class LcdHelper
{
    LiquidCrystal_I2C *lcd;
    static LcdHelper* instance;
    LcdHelper();
public:
    static LcdHelper* get();
    
    void init();

    void turnoffBacklight();
    void animFadeIn();
    void animFadeOut();
    void setCursor(uint8_t onoff, uint8_t blink);
    void setPosition(uint8_t x, uint8_t y);
    void print(char ch);
    void print(const char *str);
    void clear();
    void setBacklight(bool onOff);

    LiquidCrystal_I2C* device();
};

#endif