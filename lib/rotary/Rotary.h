#ifndef GARDEN_PUMP_ROTARY_H
#define GARDEN_PUMP_ROTARY_H

#include "Arduino.h"

#define HALF_STEP
#define ENABLE_PULLUPS

#define DIR_NONE 0x0
#define DIR_CW 0x10
#define DIR_CCW 0x20

class Rotary {
public:
    Rotary(char, char);
    unsigned char process();
private:
    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;
};

#endif //GARDEN_PUMP_ROTARY_H
