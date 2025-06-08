#include "Application.h"
#include "RelayEditController.h"
#include "LcdHelper.h"
#include "RelayState.h"

RelayEditController::RelayEditController(string name) : Controller(name) {
}

void RelayEditController::setup() {
}

void RelayEditController::loop() {
    char key = Application::get()->getKeypad()->getKey();

    if (key) {
        if (key == '*') {
            Application::get()->setControllerAsCurrent("Main");
        } else if (state == RelayEditState::SET_ON_TIME && key == whichRelay) {
            RelayState::get()->toggle(whichRelay);
            updateRelayStateInEdit();
        } else if (key == '#') {
            char H[3] = { timeToSet[0], timeToSet[1], 0 };
            char M[3] = { timeToSet[3], timeToSet[4], 0 };
            char S[3] = { timeToSet[6], timeToSet[7], 0 };
            if (state == RelayEditState::SET_ON_TIME) {
                RelayState::get()->setRelayOnTime(whichRelay, atoi(H), atoi(M), atoi(S));
                state = RelayEditState::SET_OFF_TIME;
                showRelayTime(whichRelay, "wylacz");
            }else if (state == RelayEditState::SET_OFF_TIME) {
                RelayState::get()->setRelayOffTime(whichRelay, atoi(H), atoi(M), atoi(S));
                RelayState::get()->save();
                Application::get()->setControllerAsCurrent("Main");
            }
        } else if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') {
            if (idx == 0 && (key == '0' || key == '1' || key == '2')) {
                timeToSet[idx++] = key;
            } else if (idx == 1 && (timeToSet[0] == '0' || timeToSet[0] == '1')) {
                timeToSet[idx++] = key;
            } else if (idx == 1 && timeToSet[0] == '2' && (key == '0' || key == '1' || key == '2' || key == '3')) {
                timeToSet[idx++] = key;
            } else if ((idx == 3 || idx == 6) && key >= '0' && key <= '5') {
                timeToSet[idx++] = key;
            } else if (idx == 4 || idx == 7) {
                timeToSet[idx++] = key;
            }

            if (idx == 2 || idx == 5) {
                timeToSet[idx++] = ':';
            }

            LcdHelper::get()->setPosition(0, 1);
            LcdHelper::get()->print(timeToSet);
            LcdHelper::get()->setPosition(idx, 1);
        }
    }
}

void RelayEditController::show() {
    state = RelayEditState::SET_ON_TIME;
    Application::get()->pauseBacklightDimming();
    LcdHelper::get()->setBacklight(true);
    LcdHelper::get()->setCursor(1, 1);
    LcdHelper::get()->clear();
}

void RelayEditController::hide() {
    Application::get()->resumeBacklightDimming();
    LcdHelper::get()->setCursor(0, 0);
}

void RelayEditController::setWhichRelay(char which) {
    whichRelay = which;
    showRelayTime(whichRelay, "wlacz");
}

void RelayEditController::updateRelayStateInEdit() {
    LcdHelper::get()->setPosition(15, 0);
    if (RelayState::get()->isRelayOn(whichRelay)) {
        LcdHelper::get()->print(0x1);
    } else {
        LcdHelper::get()->print(0x2);
    }
    LcdHelper::get()->setPosition(0, 1);
}

void RelayEditController::showRelayTime(char relay, const char* onoff) {
    idx = 0;

    updateRelayStateInEdit();

    LcdHelper::get()->setPosition(0, 0);
    LcdHelper::get()->print(relay);
    LcdHelper::get()->print(' ');
    LcdHelper::get()->print(onoff);

    if (state == RelayEditState::SET_ON_TIME) {
        const char* time = RelayState::get()->getRelayOnTimeAsString(relay);
        memcpy(timeToSet, time, 9);
    } else {
        const char* time = RelayState::get()->getRelayOffTimeAsString(relay);
        memcpy(timeToSet, time, 9);
    }

    LcdHelper::get()->setPosition(0, 1);
    LcdHelper::get()->print(timeToSet);
    LcdHelper::get()->setPosition(0, 1);
}
