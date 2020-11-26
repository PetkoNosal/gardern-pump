#include "Servos.h"
#include <Servo.h>

#define PIN_MOTOR 11
#define PIN_IN_STREAM 10
#define PIN_IN_BARREL 9
#define PIN_OUT_BARREL 5
#define PIN_OUT_HOSE 6

typedef struct {
    Servo valve_in_stream;
    Servo valve_in_barrel;
    Servo valve_out_barrel;
    Servo valve_out_hose;
} servos_t;

static servos_t servos;

void drivePump(byte _percentage);
void setServo(Servo &_servo, bool _state);

void Servos::init() {
    pinMode(PIN_MOTOR, OUTPUT);
    servos.valve_in_stream.attach(PIN_IN_STREAM);
    servos.valve_in_barrel.attach(PIN_IN_BARREL);
    servos.valve_out_barrel.attach(PIN_OUT_BARREL);
    servos.valve_out_hose.attach(PIN_OUT_HOSE);

    drivePump(0);
    setServo(servos.valve_in_stream, false);
    setServo(servos.valve_in_barrel, false);
    setServo(servos.valve_out_barrel, false);
    setServo(servos.valve_out_hose, false);
}

void Servos::actOnChanges(update_t &_update, state_t &_state) {
    if (_update.servos) {
        _update.servos = false;
        drivePump(_state.motorSpeed);
        setServo(servos.valve_in_stream, _state.valve_in_stream);
        setServo(servos.valve_in_barrel, _state.valve_in_barrel);
        setServo(servos.valve_out_barrel,_state.valve_out_barrel);
        setServo(servos.valve_out_hose, _state.valve_out_hose);
    }
}

void setServo(Servo &_servo, bool _state) {
    if (_state) {
        _servo.write(120);
    } else {
        _servo.write(20);
    }
}

void drivePump(byte _percentage) {
    int pulselength = map(_percentage, 0, 100, 0, 255);
    analogWrite(PIN_MOTOR, pulselength);
}