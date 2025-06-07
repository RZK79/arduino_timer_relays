#include <Arduino.h>
#include "Timer.h"

Timer::Timer() {
    timeout = 0;
    paused = false;
    callback = nullptr;
    startMillis = millis();
}

Timer::~Timer() {
}

void Timer::update() {
    if (paused) {
        return;
    }

    if (millis() - startMillis >= timeout) {
        if (callback != nullptr) {
            callback(this);
        }
        startMillis = millis();
    }
}

void Timer::start(unsigned long t, void (*_callback)(Timer* timer)) {
    timeout = t;
    startMillis = millis();
    callback = _callback;
}

void Timer::stop() {
    startMillis = millis();
}

void Timer::pause() {
    paused = true;
}

void Timer::resume() {
    paused = false;
}

void Timer::reset() {
    startMillis = millis();
}

bool Timer::isPaused() {
    return paused;
}