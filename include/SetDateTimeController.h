#ifndef _SETDATETIMECONTROLLER_H_
#define _SETDATETIMECONTROLLER_H

#include <string>
#include "Controller.h"

class SetDateTimeController : public Controller {
public:
    SetDateTimeController(string name);

    virtual void show();
    virtual void hide();
    
    virtual void setup();
    virtual void loop();
};

#endif