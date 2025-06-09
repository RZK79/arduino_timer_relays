#ifndef _APPLICATION_H_
#define _APPLICATION_H

#include <Arduino.h>
#include <Bonezegei_DS3231.h>
#include <Keypad.h>
#include <vector>
#include "Timer.h"
#include "TimerEventListener.h"
#include "Controller.h"
#include "RelayState.h"

using namespace std;

class Application : public TimerEventListener{
    static Application* instance;
    Application();

    char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'} };

    byte rowPins[4] = { 5, 6, 7, 8 };
    byte colPins[4] = { 9, 10, 11, 12 };

    Keypad* keypad;
    Bonezegei_DS3231* rtc;
    Timer* dimmTimer;

    vector<Controller*> controllers;
    Controller* currentController = nullptr;

    void showSplashScreen();
public:
    static Application* get();

    void setup();
    void loop();

    template<class T> T* getControllerByName(string name) {
        for (int i = 0; i < controllers.size(); i++) {
            if (controllers[i]->getName() == name) {
                return static_cast<T*>(controllers[i]);
            }
        }
    }

    template<class T> T* getCurrentController() {
        return static_cast<T*>(currentController);
    }

    void setControllerAsCurrent(string name);
    void pauseBacklightDimming();
    void resumeBacklightDimming();

    void onTime(Timer *timer) override;

    Bonezegei_DS3231* getRTC();
    Keypad* getKeypad();
};

#endif