#ifndef GARDEN_PUMP_SERVOS_H
#define GARDEN_PUMP_SERVOS_H
#include <Arduino.h>
#include "Objects.h"

class Servos {
public:
    void init();
    void actOnChanges(update_t &_update, state_t &_state);

private:
};

#endif //GARDEN_PUMP_SERVOS_H
