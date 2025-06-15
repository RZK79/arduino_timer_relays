#include "Application.h"
#include "MainController.h"
#include "RelayEditController.h"
#include "Constants.h"
#include "LcdHelper.h"
#include "RelayState.h"

MainController::MainController(string name) : Controller(name) {

}

void MainController::onTime(Timer* timer) {
    if (timer == updateTimer) {
        char d[32] = { 0 };

        if (Application::get()->getRTC()->getTime()) {
            if (Application::get()->getRTC()->getHour() > 9) {
                sprintf(d, "%02d", Application::get()->getRTC()->getHour());
            } else {
                sprintf(d, " %1d", Application::get()->getRTC()->getHour());
            }

            LcdHelper::get()->setPosition(0, 0);
            LcdHelper::get()->print(d);
            LcdHelper::get()->print(":");
            sprintf(d, "%02d", Application::get()->getRTC()->getMinute());
            LcdHelper::get()->print(d);
            LcdHelper::get()->print(":");
            sprintf(d, "%02d", Application::get()->getRTC()->getSeconds());
            LcdHelper::get()->print(d);

            LcdHelper::get()->setPosition(0, 1);
            sprintf(d, "%02d/%02d/%02d", Application::get()->getRTC()->getYear(), Application::get()->getRTC()->getMonth(), Application::get()->getRTC()->getDate());
            LcdHelper::get()->print(d);
        }

        LcdHelper::get()->setPosition(8, 0);
        LcdHelper::get()->print(0x7c);
        LcdHelper::get()->print("A B C D");
        LcdHelper::get()->setPosition(8, 1);
        LcdHelper::get()->print(0x7c);

        char relays[4] = { 'A', 'B' ,'C', 'D' };

        for (uint i = 0;i < sizeof(relays);i++) {
            if (RelayState::get()->isRelayOn(relays[i])) {
                LcdHelper::get()->print(0x1);
            } else {
                LcdHelper::get()->print(0x2);
            }

            LcdHelper::get()->print(" ");
        }
    }
}

void MainController::setup() {
    updateTimer = new Timer();
    updateTimer->addEventListener(this);
    updateTimer->start(RTC_INTERVAL);
    updateTimer->pause();
}

void MainController::loop() {
    updateTimer->update();

    char key = Application::get()->getKeypad()->getKey();

    if (key && (key == 'A' || key == 'B' || key == 'C' || key == 'D')) {
        Application::get()->setControllerAsCurrent("RelayEdit");
        Application::get()->getCurrentController<RelayEditController>()->setWhichRelay(key);
    }else if(key == '*'){
        Application::get()->setControllerAsCurrent("SetDateTime");
    }
}

void MainController::show() {
    updateTimer->resume();
}

void MainController::hide() {
    updateTimer->pause();
}
