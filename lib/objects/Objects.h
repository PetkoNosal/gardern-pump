#ifndef GARDEN_PUMP_OBJECTS_H
#define GARDEN_PUMP_OBJECTS_H

typedef struct {
    bool display;
    bool servos;
} update_t;

typedef struct {
    bool pump;
    bool valve_in_stream;
    bool valve_in_barrel;
    bool valve_out_barrel;
    bool valve_out_hose;
    byte selected;
    byte motorSpeed;
    bool buzzer;
} state_t;

typedef struct {
    double rawVoltage;
    byte rawFlow;
    byte percentageVoltage;
    byte percentageFlow;
} monitor_t;

#endif //GARDEN_PUMP_OBJECTS_H
