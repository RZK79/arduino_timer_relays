#ifndef _RELAYEDITCONTROLLER_H_
#define _RELAYEDITCONTROLLER_H

#include <Arduino.h>
#include <string>
#include <vector>
#include "Controller.h"

using namespace std;

class RelayEditController : public Controller {
    enum RelayEditState{
        SET_ON_TIME,
        SET_OFF_TIME
    };

    RelayEditState state;

    uint8_t idx;
    char timeToSet[9];
    char whichRelay;

    void showRelayTime(char relay, const char* onoff);
    void updateRelayStateInEdit();
public:
    RelayEditController(string name);
  
    virtual void setup();
    virtual void loop();
    virtual void show();
    virtual void hide();

    void setWhichRelay(char which);
};

#endif