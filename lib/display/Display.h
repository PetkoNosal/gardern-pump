#ifndef GARDEN_PUMP_DISPLAY_H
#define GARDEN_PUMP_DISPLAY_H

#include <Arduino.h>
#include "Objects.h"

class Display {
public:
    void init();
    void redrawDisplay(update_t &_update, state_t &_state, monitor_t &_monitor);

private:
    static void drawConfig(state_t &_state, monitor_t &_monitor);
    static void drawAction(state_t &_state);
    static void drawOverlay(state_t &_state);
    static void drawStatic();
};

#endif //GARDEN_PUMP_DISPLAY_H
