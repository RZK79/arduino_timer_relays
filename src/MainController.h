#ifndef _MAINCONTROLLER_H_
#define _MAINCONTROLLER_H

#include <string>
#include "Controller.h"
#include "Timer.h"
#include "TimerEventListener.h"

using namespace std;

class MainController : public Controller, TimerEventListener {
    Timer* updateTimer;
public:
    MainController(string name);

    void onTime(Timer *timer) override;

    virtual void setup();
    virtual void loop();

    virtual void show();
    virtual void hide();
};

#endif