#include "Servos.h"
#include <Servo.h>

#define SERVO_DELAY 500

/// SERVO FOR VALVE IN-STREAM ////
#define IN_STREAM_PIN 5
#define IN_STREAM_MIN 20
#define IN_STREAM_MAX 95
//////////////////////////////////

/// SERVO FOR VALVE IN-BARREL ////
#define IN_BARREL_PIN 6
#define IN_BARREL_MIN 20
#define IN_BARREL_MAX 110
//////////////////////////////////

/// SERVO FOR VALVE OUT-BARREL ///
#define OUT_BARREL_PIN 10
#define OUT_BARREL_MIN 20
#define OUT_BARREL_MAX 120
//////////////////////////////////

/// SERVO FOR VALVE OUT-HOSE /////
#define OUT_HOSE_PIN 9
#define OUT_HOSE_MIN 20
#define OUT_HOSE_MAX 100
//////////////////////////////////

/// PUMP /////////////////////////
#define MOTOR_PIN 11
#define MOTOR_MIN 20
#define MOTOR_MAX 80
//////////////////////////////////

typedef struct {
    Servo servo;
    byte pin;
    byte min;
    byte max;
    bool state;
} valve_servo_t;

typedef struct servos {
    valve_servo_t valve_in_stream = {Servo(), IN_STREAM_PIN, IN_STREAM_MIN, IN_STREAM_MAX, true};
    valve_servo_t valve_in_barrel = {Servo(), IN_BARREL_PIN, IN_BARREL_MIN, IN_BARREL_MAX, true};
    valve_servo_t valve_out_barrel = {Servo(), OUT_BARREL_PIN, OUT_BARREL_MIN, OUT_BARREL_MAX, true};
    valve_servo_t valve_out_hose = {Servo(), OUT_HOSE_PIN, OUT_HOSE_MIN, OUT_HOSE_MAX, true};
    valve_servo_t pump = {Servo(), MOTOR_PIN, MOTOR_MIN, MOTOR_MAX, true};
} servos_t;

static servos_t servos;

void drivePump(valve_servo_t &_servo, byte _percentage);
void setServo(valve_servo_t &_servo, bool _state);

void Servos::init() {
    servos.pump.servo.attach(servos.pump.pin);
    servos.valve_in_stream.servo.attach(servos.valve_in_stream.pin);
    servos.valve_in_barrel.servo.attach(servos.valve_in_barrel.pin);
    servos.valve_out_barrel.servo.attach(servos.valve_out_barrel.pin);
    servos.valve_out_hose.servo.attach(servos.valve_out_hose.pin);
}

void Servos::actOnChanges(update_t &_update, state_t &_state) {
    if (_update.servos) {
        _update.servos = false;
        drivePump(servos.pump, _state.motorSpeed);
        setServo(servos.valve_in_stream, _state.valve_in_stream);
        setServo(servos.valve_in_barrel, _state.valve_in_barrel);
        setServo(servos.valve_out_barrel,_state.valve_out_barrel);
        setServo(servos.valve_out_hose, _state.valve_out_hose);
    }
}

void setServo(valve_servo_t &_servo, bool _state) {
    if (_state != _servo.state) {
        if (_state) {
            _servo.servo.write(_servo.max + 15);
            delay(SERVO_DELAY);
            _servo.servo.write(_servo.max);
        } else {
            _servo.servo.write(_servo.min - 15);
            delay(SERVO_DELAY);
            _servo.servo.write(_servo.min);
        }
        _servo.state = _state;
    }
}

void drivePump(valve_servo_t &_servo, byte _percentage) {
    int pulselength = map(_percentage, 0, 100, _servo.min, _servo.max);
    _servo.servo.write(pulselength);
}
