#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino.h>
#include <map>

using namespace std;

struct Config {
    static std::map<char, uint8_t> relay_pin;
};

std::map<char, uint8_t> Config::relay_pin = {
    {'A', 2},
    {'B', 3},
    {'C', 4},
    {'D', 13}
};

#endif