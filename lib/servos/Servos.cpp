#include "Servos.h"
#include <Servo.h>

typedef struct {
    Servo pump;
    Servo valve_in_stream;
    Servo valve_in_barrel;
    Servo valve_out_barrel;
    Servo valve_out_hose;
} servos_t;

static servos_t servos;

void driveServo(Servo &_servo, byte _percentage);
void setServo(Servo &_servo, bool _state);

void Servos::init() {
    servos.pump.attach(11);
    servos.valve_in_stream.attach(10);
    servos.valve_in_barrel.attach(9);
    servos.valve_out_barrel.attach(5);
    servos.valve_out_hose.attach(6);

    driveServo(servos.pump, 0);
    driveServo(servos.valve_in_stream, 0);
    driveServo(servos.valve_in_barrel, 0);
    driveServo(servos.valve_out_barrel, 0);
    driveServo(servos.valve_out_hose, 0);
}

void Servos::actOnChanges(update_t &_update, state_t &_state) {
    if (_update.servos) {
        _update.servos = false;
        driveServo(servos.pump, _state.motorSpeed);
        setServo(servos.valve_in_stream, _state.valve_in_stream);
        setServo(servos.valve_in_barrel, _state.valve_in_barrel);
        setServo(servos.valve_out_barrel,_state.valve_out_barrel);
        setServo(servos.valve_out_hose, _state.valve_out_hose);
    }
}

void setServo(Servo &_servo, bool _state) {
    if (_state) {
        driveServo(_servo, 60);
    } else {
        driveServo(_servo, 10);
    }
}

void driveServo(Servo &_servo, byte _percentage) {
    int pulselength = map(_percentage, 0, 100, 10, 180);
    _servo.write(pulselength);
}