#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <string>

using namespace std;

class Controller
{
    string name;
public:
    Controller(string _name);

    const string& getName();

    virtual void show();
    virtual void hide();
    
    virtual void setup();
    virtual void loop();
};

#endif