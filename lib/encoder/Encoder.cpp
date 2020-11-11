#include "Encoder.h"

#define ENCODER_CLK 2
#define ENCODER_DT 3
#define ENCODER_SW 4

static bool currentStateCLK;
static bool lastStateCLK;
static bool lastStateSW = HIGH;
static bool currentStateSW;
static unsigned long pressedTime = 0;
static unsigned long releasedTime = 0;

void Encoder::init() {
    pinMode(ENCODER_CLK, INPUT);
    pinMode(ENCODER_DT, INPUT);
    pinMode(ENCODER_SW, INPUT_PULLUP);
    lastStateCLK = digitalRead(ENCODER_CLK);
}

void Encoder::checkActivity(update_t &_update, state_t &_state) {
    currentStateCLK = digitalRead(ENCODER_CLK);
    if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
        if (digitalRead(ENCODER_DT) != currentStateCLK) {
            computeRotation(false, _update, _state);
        } else {
            computeRotation(true, _update, _state);
        }
        _update.display = true;
    }
    lastStateCLK = currentStateCLK;

    currentStateSW = digitalRead(ENCODER_SW);
    if (lastStateSW == HIGH && currentStateSW == LOW) {
        pressedTime = millis();
    } else if (lastStateSW == LOW && currentStateSW == HIGH) {
        releasedTime = millis();
        unsigned long pressDuration = releasedTime - pressedTime;
        if (pressDuration < 500) {
            interact(_state);
            _update.display = true;
            _update.servos = true;
        } else {
            config();
        }
    }
    lastStateSW = currentStateSW;
    delay(10);
}

void Encoder::computeRotation(bool _add, update_t &_update, state_t &_state) {
    if (_state.pump) {
        if (_add) {
            if (_state.motorSpeed < 100) {
                _state.motorSpeed = _state.motorSpeed + 10;
            }
        } else {
            if (_state.motorSpeed > 0) {
                _state.motorSpeed = _state.motorSpeed - 10;
            }
        }
        _update.servos = true;
    } else {
        if (_add) {
            if (_state.selected == 4) {
                _state.selected = 0;
            } else {
                _state.selected++;
            }
        } else {
            if (_state.selected == 0) {
                _state.selected = 4;
            } else {
                _state.selected--;
            }
        }
    }
}

void Encoder::interact(state_t &_state) {
    if (_state.selected == 0) {
        _state.pump = !_state.pump;
    }
    if (_state.selected == 1) {
        _state.valve_in_stream = !_state.valve_in_stream;
    }
    if (_state.selected == 2) {
        _state.valve_in_barrel = !_state.valve_in_barrel;
    }
    if (_state.selected == 3) {
        _state.valve_out_barrel = !_state.valve_out_barrel;
    }
    if (_state.selected == 4) {
        _state.valve_out_hose = !_state.valve_out_hose;
    }
}

void Encoder::config() {
    // LONG PRESS OF BUTTON
}