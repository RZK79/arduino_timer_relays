#include "RelayState.h"
#include <EEPROM.h>
#include "Config.h"

RelayState* RelayState::instance = nullptr;

RelayState* RelayState::get() {
    if (instance == nullptr) {
        instance = new RelayState();
    }

    return instance;
}

RelayState::RelayState() {
    relays = {
        {'A', Relay()},
        {'B', Relay()},
        {'C', Relay()},
        {'D', Relay()},
    };

    relays['A'].clear();
    relays['B'].clear();
    relays['C'].clear();
    relays['D'].clear();

    pinMode(Config::relay_pin['A'], OUTPUT);
    pinMode(Config::relay_pin['B'], OUTPUT);
    pinMode(Config::relay_pin['C'], OUTPUT);
    pinMode(Config::relay_pin['D'], OUTPUT);
}

void RelayState::load() {
    EEPROM.get(0, relays['A']);
    EEPROM.get(1, relays['B']);
    EEPROM.get(2, relays['C']);
    EEPROM.get(3, relays['D']);
}

void RelayState::save() {
    EEPROM.put(0, relays['A']);
    EEPROM.put(1, relays['B']);
    EEPROM.put(2, relays['C']);
    EEPROM.put(3, relays['D']);
}

void RelayState::turnOffAllRelays() {
    digitalWrite(Config::relay_pin['A'], HIGH);
    relays['A'].isOn = false;

    digitalWrite(Config::relay_pin['B'], HIGH);
    relays['B'].isOn = false;

    digitalWrite(Config::relay_pin['C'], HIGH);
    relays['C'].isOn = false;

    digitalWrite(Config::relay_pin['D'], HIGH);
    relays['D'].isOn = false;
}

void RelayState::toggle(char relay) {
    if (relays[relay].isOn) {
        digitalWrite(Config::relay_pin[relay], HIGH);
        relays[relay].isOn = false;
    } else {
        digitalWrite(Config::relay_pin[relay], LOW);
        relays[relay].isOn = true;
    }
}

bool RelayState::isRelayOn(char relay) {
    return relays[relay].isOn;
}

void RelayState::setRelayOnTime(char relay, int H, int M, int S) {
    relays[relay].relayOnH = H;
    relays[relay].relayOnM = M;
    relays[relay].relayOnS = S;
}

void RelayState::setRelayOffTime(char relay, int H, int M, int S) {
    relays[relay].relayOffH = H;
    relays[relay].relayOffM = M;
    relays[relay].relayOffS = S;
}

const char* RelayState::getRelayOnTimeAsString(char relay) {    
    sprintf(timeString, "%02d:%02d:%02d", relays[relay].relayOnH, relays[relay].relayOnM, relays[relay].relayOnS);
    return timeString;
}

const char* RelayState::getRelayOffTimeAsString(char relay) {
    sprintf(timeString, "%02d:%02d:%02d", relays[relay].relayOffH, relays[relay].relayOffM, relays[relay].relayOffS);
    return timeString;
}