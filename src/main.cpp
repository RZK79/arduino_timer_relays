#include "Application.h"

void setup() {
    Application::get()->setup();
}

void loop() {
    Application::get()->loop();
}
