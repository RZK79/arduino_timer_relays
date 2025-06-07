#include "Application.h"
#include "RelayEditController.h"
#include "LcdHelper.h"
#include "RelayState.h"

RelayEditController::RelayEditController(string name) : Controller(name) {
}

void RelayEditController::setup() {
    timeToSet[0] = 0;
    currentEditPos = 0;
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
            char H[3] = { 0, 0, 0 };
            char M[3] = { 0, 0, 0 };
            char S[3] = { 0, 0, 0 };

            H[0] = timeToSet[0];
            H[1] = timeToSet[1];
            M[0] = timeToSet[3];
            M[1] = timeToSet[4];
            S[0] = timeToSet[6];
            S[1] = timeToSet[7];

            if (state == RelayEditState::SET_ON_TIME) {
                RelayState::get()->setRelayOnTime(whichRelay, atoi(H), atoi(M), atoi(S));
                showRelayTime(whichRelay, "wylacz");
                state = RelayEditState::SET_OFF_TIME;
            } else if (state == RelayEditState::SET_OFF_TIME) {
                RelayState::get()->setRelayOffTime(whichRelay, atoi(H), atoi(M), atoi(S));
                Application::get()->setControllerAsCurrent("Main");
            }
        } else if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') {
            if (currentEditPos == 0 && (key == '0' || key == '1' || key == '2')) {
                setAndGoToNext(key);
            } else if (currentEditPos == 1 && (timeToSet[currentEditPos - 1] == '0' || timeToSet[currentEditPos - 1] == '1')) {
                setAndGoToNext(key);
            } else if (currentEditPos == 1 && timeToSet[currentEditPos - 1] == '2' && (key == '0' || key == '1' || key == '2' || key == '3')) {
                setAndGoToNext(key);
            } else if (currentEditPos == 3 && key >= '0' && key <= '5') {
                setAndGoToNext(key);
            } else if (currentEditPos == 6 && key >= '0' && key <= '5') {
                setAndGoToNext(key);
            } else if (currentEditPos == 4 || currentEditPos == 7) {
                setAndGoToNext(key);
            }
        }
    }
}

void RelayEditController::show() {
    state = RelayEditState::SET_ON_TIME;
    Application::get()->pauseBacklightDimming();
    LcdHelper::get()->setBacklight(true);
    LcdHelper::get()->setCursor(1, 1);
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
    clearTimeToSet();

    currentEditPos = 0;

    LcdHelper::get()->clear();
    
    updateRelayStateInEdit();

    LcdHelper::get()->setPosition(0, 0);
    LcdHelper::get()->print(relay);
    LcdHelper::get()->print(' ');
    LcdHelper::get()->print(onoff);
    LcdHelper::get()->setPosition(0, 1);
    if (state == RelayEditState::SET_ON_TIME) {
        LcdHelper::get()->print(RelayState::get()->getRelayOnTimeAsString(relay));
    } else {
        LcdHelper::get()->print(RelayState::get()->getRelayOffTimeAsString(relay));
    }
    LcdHelper::get()->setPosition(0, 1);
}

void RelayEditController::setAndGoToNext(char key) {
    LcdHelper::get()->print(key);

    timeToSet[currentEditPos] = key;

    currentEditPos++;

    if (currentEditPos == 2 || currentEditPos == 5) {
        currentEditPos++;
        LcdHelper::get()->setPosition(currentEditPos, 1);
    }
}

void RelayEditController::clearTimeToSet() {
    for (int i = 0; i < 8; i++) {
        timeToSet[i] = 0x20;
    }
    timeToSet[8] = 0;
}
