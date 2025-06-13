#include "Application.h"
#include "LcdHelper.h"
#include "SetDateTimeController.h"

SetDateTimeController::SetDateTimeController(string name) : Controller(name) {

}

void SetDateTimeController::show() {
    Application::get()->pauseBacklightDimming();
    LcdHelper::get()->setBacklight(true);
    LcdHelper::get()->setCursor(1, 1);
    LcdHelper::get()->clear();
}

void SetDateTimeController::hide() {
    Application::get()->resumeBacklightDimming();
    LcdHelper::get()->setCursor(0, 0);
}

void SetDateTimeController::setup() {

}

void SetDateTimeController::loop() {
    char key = Application::get()->getKeypad()->getKey();

    if (key) {
        if (key == '*') {
            Application::get()->setControllerAsCurrent("Main");
        }
    }
}