#ifndef _MAINCONTROLLER_H_
#define _MAINCONTROLLER_H

#include <string>
#include "Controller.h"
#include "Timer.h"

using namespace std;

class MainController : public Controller {
    Timer* updateTimer;
public:
    MainController(string name);

    virtual void setup();
    virtual void loop();

    virtual void show();
    virtual void hide();
};

#endif