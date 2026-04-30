#ifndef _SETDATETIMECONTROLLER_H_
#define _SETDATETIMECONTROLLER_H

#include <string>
#include "Controller.h"

class SetDateTimeController : public Controller {
    enum SetDateTimeState{
        SET_TIME,
        SET_DATE
    };

    SetDateTimeState state;
    uint8_t idx;
    char timeToSet[9];

    void showCurrentDateTime();
public:
    SetDateTimeController(string name);

    virtual void show();
    virtual void hide();
    
    virtual void setup();
    virtual void loop();
};

#endif