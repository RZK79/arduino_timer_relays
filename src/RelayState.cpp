#include <EEPROM.h>
#include "RelayState.h"
#include "Config.h"

RelayState* RelayState::instance = nullptr;

RelayState* RelayState::get() {
    if (instance == nullptr) {
        instance = new RelayState();
    }

    return instance;
}

RelayState::RelayState() {
    save_exists = 0x0;

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
    EEPROM.get(0, save_exists);
    Serial.println(save_exists, 16);
    if (save_exists != 0xcafe) {
        turnOffAllRelays();
        save();
    }

    EEPROM.get(sizeof(uint16_t), relays['A']);
    EEPROM.get(sizeof(uint16_t) + sizeof(Relay), relays['B']);
    EEPROM.get(sizeof(uint16_t) + 2 * sizeof(Relay), relays['C']);
    EEPROM.get(sizeof(uint16_t) + 3 * sizeof(Relay), relays['D']);
}

void RelayState::save() {
    save_exists = 0xcafe;
    EEPROM.put(0, save_exists);
    EEPROM.put(sizeof(uint16_t), relays['A']);
    EEPROM.put(sizeof(uint16_t) + sizeof(Relay), relays['B']);
    EEPROM.put(sizeof(uint16_t) + 2 * sizeof(Relay), relays['C']);
    EEPROM.put(sizeof(uint16_t) + 3 * sizeof(Relay), relays['D']);
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

void RelayState::toggle(char relay, bool force = false) {
    if (relays[relay].isOn) {
        digitalWrite(Config::relay_pin[relay], HIGH);
        relays[relay].isOn = false;
    } else {
        digitalWrite(Config::relay_pin[relay], LOW);
        relays[relay].isOn = true;
    }
    relays[relay].forced = force;
}

bool RelayState::isRelayOn(char relay) {
    return relays[relay].isOn;
}

bool RelayState::isForced(char relay) {
    return relays[relay].forced;
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

Relay RelayState::getRelay(char relay) {
    return relays[relay];
}

void RelayState::turnOn(char relay, bool force = false) {
    if (!relays[relay].isOn) {
        digitalWrite(Config::relay_pin[relay], LOW);
        relays[relay].isOn = true;
        relays[relay].forced = force;
    }
}

void RelayState::turnOff(char relay, bool force = false) {
    if (relays[relay].isOn) {
        digitalWrite(Config::relay_pin[relay], HIGH);
        relays[relay].isOn = false;
        relays[relay].forced = force;
    }
}