#ifndef GARDEN_PUMP_ENCODER_H
#define GARDEN_PUMP_ENCODER_H
#include <Arduino.h>
#include "Objects.h"

class Encoder {
public:
    void init();
    void checkActivity(update_t &_update, state_t &_state);

private:
    static void computeRotation(bool _add, update_t &_update, state_t &_state);
    static void interact(state_t &_state);
    void config(state_t &_state);
};

#endif //GARDEN_PUMP_ENCODER_H
