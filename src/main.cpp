#include "Application.h"

void setup() {
    Serial.begin(9600);
    Application::get()->setup();
}

void loop() {
    Application::get()->loop();
}
