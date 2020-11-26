#include "Measurement.h"

#define VOLTAGE_PIN A7
#define FLOW_PIN A6

static double minVoltage = 18.0;
static double maxVoltage = 21.0;

static double minFlow = 19.7;
static double maxFlow = 100.5;

static unsigned long lastUpdate = 0;

void Measurement::init(monitor_t &_monitor) {
    pinMode(VOLTAGE_PIN, INPUT);
    pinMode(FLOW_PIN, INPUT);

    _monitor.rawVoltage = getVoltage();
    _monitor.percentageVoltage = map(_monitor.rawVoltage, minVoltage, maxVoltage);
    _monitor.rawFlow = getFlow();
    _monitor.percentageFlow = map(_monitor.rawFlow, minFlow, maxFlow);
}

void Measurement::updateReadings(update_t &_update, monitor_t &_monitor) {
    if (millis() - lastUpdate > 1000) {
        calculateVoltage(_monitor);
        calculateFlow(_monitor);
        lastUpdate = millis();
        _update.display = true;
    }
}

void Measurement::actOnChanges(update_t &_update, state_t &_state, monitor_t &_monitor) {
    if (_monitor.percentageVoltage < 5) {
        /* ACT ON UNDERVOLTAGE */
        _update.servos = true;
        _update.display = true;

        _state.motorSpeed = 0;

        _state.valve_in_stream = false;
        _state.valve_in_barrel = false;
        _state.valve_out_barrel = false;
        _state.valve_out_hose = false;
    }

    if (_state.motorSpeed == 100 && _monitor.percentageFlow < 25) {
        /* ACT ON UNDERFLOW */
        _state.motorSpeed = 0;
        _state.valve_in_stream = false;
    }
}

void Measurement::calculateVoltage(monitor_t &_monitor) {
    double rawVoltage = getVoltage();
    bool update = false;
    if (_monitor.rawVoltage != rawVoltage) {
        if (_monitor.rawVoltage - 0.5 > rawVoltage) {
            _monitor.rawVoltage = rawVoltage;
            update = true;
        }
        if (_monitor.rawVoltage + 0.5 < rawVoltage) {
            _monitor.rawVoltage = rawVoltage;
            update = true;
        }
    }
    if (update) {
        _monitor.percentageVoltage = map(_monitor.rawVoltage, minVoltage, maxVoltage);
    }
}

void Measurement::calculateFlow(monitor_t &_monitor) {
    double rawFlow = getFlow();
    bool update = false;
    if (_monitor.rawFlow != rawFlow) {
        if (_monitor.rawFlow - 0.5 > rawFlow) {
            _monitor.rawFlow = rawFlow;
            update = true;
        }
        if (_monitor.rawFlow + 0.5 < rawFlow) {
            _monitor.rawFlow = rawFlow;
            update = true;
        }
    }
    if (update) {
        _monitor.percentageFlow = map(_monitor.rawFlow, minFlow, maxFlow);
    }
}

double Measurement::getVoltage() {
    double rawInput = (analogRead(VOLTAGE_PIN) * 5.0) / 1024.0;
    double currentVoltage = rawInput / 0.19741448963102612442768650686776;
    if (currentVoltage < minVoltage) {
        return minVoltage;
    }

    if (currentVoltage > maxVoltage) {
        return maxVoltage;
    }

    return currentVoltage;
}

double Measurement::getFlow() {
    double rawInput = (analogRead(FLOW_PIN) * 5.0) / 1024.0;
    double currentFlow = rawInput;
    if (currentFlow < minFlow) {
        return minFlow;
    }

    if (currentFlow > maxFlow) {
        return maxFlow;
    }

    return currentFlow;
}

byte Measurement::map(double x, double in_min, double in_max) {
    return ((x - in_min) * 100) / (in_max - in_min);
}