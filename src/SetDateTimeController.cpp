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

    state = SetDateTimeState::SET_TIME;

    showCurrentDateTime();

    idx = 0;
    memset(timeToSet, 0, 9);
}

void SetDateTimeController::showCurrentDateTime() {
    char buf[16] = { 0 };
    auto rtc = Application::get()->getRTC();

    rtc->getTime();

    LcdHelper::get()->setPosition(0, 0);
    uint8_t hour = rtc->getHour();
    uint8_t minute = rtc->getMinute();
    uint8_t seconds = rtc->getSeconds();
    sprintf(buf, "%.2d:%.2d:%.2d", hour > 24 ? 0 : hour, minute > 59 ? 0 : minute, seconds > 59 ? 0 : seconds);
    LcdHelper::get()->print(buf);

    LcdHelper::get()->setPosition(0, 1);
    uint8_t year = rtc->getYear();
    uint8_t month = rtc->getMonth();
    uint8_t day = rtc->getDate();
    sprintf(buf, "%.2d/%.2d/%.2d", year > 99 ? 99 : year, month > 12 ? 12 : month, day > 31 ? 1 : day);
    LcdHelper::get()->print(buf);

    LcdHelper::get()->setPosition(0, 0);
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
        } else if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') {
            if (state == SetDateTimeState::SET_TIME) {
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

                LcdHelper::get()->setPosition(0, 0);
                LcdHelper::get()->print(timeToSet);
                LcdHelper::get()->setPosition(idx, 0);
            } else {
                if (idx == 3 && (key == 0 || key == 1)) {
                    timeToSet[idx++] = key;
                } else if (idx == 4 && timeToSet[3] == 1 && (key == 0 || key == 1 || key == 2)) {
                    timeToSet[idx++] = key;
                } else if (idx == 6 && (key == 0 || key == 1 || key == 2 || key == 3)) {
                    timeToSet[idx++] = key;
                } else {
                    timeToSet[idx++] = key;
                }

                if (idx == 2 || idx == 5) {
                    timeToSet[idx++] = '/';
                }

                LcdHelper::get()->setPosition(0, 1);
                LcdHelper::get()->print(timeToSet);
                LcdHelper::get()->setPosition(idx, 1);
            }
        } else if (key == '#') {
            auto rtc = Application::get()->getRTC();

            if (state == SetDateTimeState::SET_TIME) {
                rtc->setTime(timeToSet);
                memset(timeToSet, 0, 9);
                idx = 0;
                state = SetDateTimeState::SET_DATE;
                LcdHelper::get()->setPosition(0, 1);
            } else if (state == SetDateTimeState::SET_DATE) {
                char buf[10] = { timeToSet[3], timeToSet[4], '/', timeToSet[6], timeToSet[7],'/', timeToSet[0], timeToSet[1], '\0' };
                rtc->setDate(buf);
                Application::get()->setControllerAsCurrent("Main");
            }
        }
    }
}