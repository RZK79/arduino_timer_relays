#include "Application.h"
#include "MainController.h"
#include "RelayEditController.h"
#include "Constants.h"
#include "LcdHelper.h"

Application* Application::instance = nullptr;

void Application::onTime(Timer *timer){
    if(timer == dimmTimer){
        LcdHelper::get()->turnoffBacklight();
    }
}

Application* Application::get() {
    if (instance == nullptr) {
        instance = new Application();
    }

    return instance;
}

Application::Application() {
}

void Application::showSplashScreen() {
    LcdHelper::get()->clear();
    LcdHelper::get()->print("Witaj");
    LcdHelper::get()->setPosition(0, 1);
    LcdHelper::get()->print("Krzysztofie ");
    LcdHelper::get()->device()->write(0);

    delay(1000);

    LcdHelper::get()->animFadeIn();
    LcdHelper::get()->animFadeOut();

    LcdHelper::get()->clear();
}

void Application::setup() {
    keypad = new Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
    rtc = new Bonezegei_DS3231(0x68);

    controllers.push_back(new MainController("Main"));
    controllers.push_back(new RelayEditController("RelayEdit"));

    for (uint i = 0;i < controllers.size();i++) {
        controllers[i]->setup();
    }
    
    LcdHelper::get()->init();
    LcdHelper::get()->setBacklight(true);
    
    showSplashScreen();
    
    setControllerAsCurrent("Main");

    dimmTimer = new Timer();
    dimmTimer->addEventListener(this);
    dimmTimer->start(BACKLIGHT_DIMM_AFTER);
    dimmTimer->pause();

    rtc->begin();
    rtc->setFormat(24);

    RelayState::get()->turnOffAllRelays();
    RelayState::get()->load();

    dimmTimer->resume();
}

void Application::loop() {
    currentController->loop();
    dimmTimer->update();


    //TODO: sprawdzenie czasu i włączenie przekaznikow
}

void Application::setControllerAsCurrent(string name) {
    for (uint i = 0; i < controllers.size(); i++) {
        if (controllers[i]->getName() == name) {
            if(currentController != nullptr){
                currentController->hide();
            }
            currentController = controllers[i];
            currentController->show();
        }
    }
}

Bonezegei_DS3231* Application::getRTC() {
    return rtc;
}

Keypad* Application::getKeypad() {
    return keypad;
}

void Application::pauseBacklightDimming() {
    dimmTimer->pause();
}

void Application::resumeBacklightDimming() {
    dimmTimer->resume();
    dimmTimer->reset();
}