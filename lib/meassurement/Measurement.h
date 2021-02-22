#ifndef GARDEN_PUMP_MEASUREMENT_H
#define GARDEN_PUMP_MEASUREMENT_H
#include <Arduino.h>
#include "Objects.h"

class Measurement {
public:
    void init(monitor_t &_monitor);
    void updateReadings(update_t &_update, state_t &_state, monitor_t &_monitor);
    void actOnChanges(update_t &_update, state_t &_state, monitor_t &_monitor);

private:
    double getVoltage();
    void calculateVoltage(monitor_t &_monitor);
    byte getFlow();
    static void countFlow();
    void calculateFlow(monitor_t &_monitor);
    byte map(double x, double in_min, double in_max);
    void updateBuzzer(bool state);
};

#endif //GARDEN_PUMP_MEASUREMENT_H
