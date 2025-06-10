#ifndef _RELAYSTATE_H_
#define _RELAYSTATE_H_

#include <Arduino.h>
#include <map>

using namespace std;

typedef struct
{
    uint8_t relayOnH;
    uint8_t relayOnM;
    uint8_t relayOnS;
    uint8_t relayOffH;
    uint8_t relayOffM;
    uint8_t relayOffS;

    bool isOn;

    void clear() {
        relayOnH = 0;
        relayOnM = 0;
        relayOnS = 0;
        relayOffH = 0;
        relayOffM = 0;
        relayOffS = 0;

        isOn = false;
    }

    void toggle() {
        isOn = !isOn;
    }
} Relay;

class RelayState
{
    RelayState();
    static RelayState* instance;
    
    std::map<char, Relay> relays;
    char timeString[9];

    uint16_t save_exists;
public:
    static RelayState* get();

    void load();
    void save();

    void turnOffAllRelays();
    void toggle(char relay);
    void turnOn(char relay);
    void turnOff(char relay);

    bool isRelayOn(char relay);
    void setRelayOnTime(char relay, int H, int M, int S);
    void setRelayOffTime(char relay, int H, int M, int S);
    const char* getRelayOnTimeAsString(char relay);
    const char* getRelayOffTimeAsString(char relay);

    Relay getRelay(char relay);
};

#endif