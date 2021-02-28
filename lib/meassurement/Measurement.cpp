#include "Measurement.h"

#define VOLTAGE_PIN A7
#define FLOW_PIN A6
#define BUZZER_PIN 7

static double minVoltage = 18.0;
static double maxVoltage = 21.0;

static double minFlow = 19.7;
static double maxFlow = 100.5;

byte underVoltage = 0;
byte underFlow = 0;
byte treshold = 5;

volatile byte flowCount = 0;

static unsigned long lastUpdate = 0;

void Measurement::init(monitor_t &_monitor) {
    pinMode(VOLTAGE_PIN, INPUT);
    attachInterrupt(FLOW_PIN, countFlow, RISING);
    pinMode(BUZZER_PIN, OUTPUT);

    interrupts();

    _monitor.rawVoltage = getVoltage();
    _monitor.percentageVoltage = map(_monitor.rawVoltage, minVoltage, maxVoltage);
    _monitor.rawFlow = getFlow();
    _monitor.percentageFlow = map(_monitor.rawFlow, minFlow, maxFlow);
}

void Measurement::updateReadings(update_t &_update, state_t &_state, monitor_t &_monitor) {
    if (millis() - lastUpdate > 1000) {
        calculateVoltage(_monitor);
        calculateFlow(_monitor);

        if (_monitor.percentageVoltage < 5) {
            underVoltage++;
        } else {
            underVoltage = 0;
        }

        if (_state.motorSpeed == 100 && _monitor.percentageFlow < 25) {
            underFlow++;
        } else {
            underFlow = 0;
        }

        lastUpdate = millis();
        _update.display = true;
    }
}

void Measurement::actOnChanges(update_t &_update, state_t &_state, monitor_t &_monitor) {
    if (underVoltage >= treshold) {
        /* ACT ON UNDERVOLTAGE */
        _update.servos = true;
        _update.display = true;

        _state.motorSpeed = 0;

        _state.valve_in_stream = false;
        _state.valve_in_barrel = false;
        _state.valve_out_barrel = false;
        _state.valve_out_hose = false;

        _state.buzzer = true;
    }

    if (underFlow >= treshold) {
        /* ACT ON UNDERFLOW */
        _update.servos = true;
        _update.display = true;

        _state.motorSpeed = 0;

        _state.valve_in_stream = false;
        _state.buzzer = true;
    }

    updateBuzzer(_state.buzzer);
}

void Measurement::calculateVoltage(monitor_t &_monitor) {
    double rawVoltage = getVoltage();
    bool update = false;
    if (_monitor.rawVoltage != rawVoltage) {
        if (_monitor.rawVoltage - 0.5 > rawVoltage || _monitor.rawVoltage + 0.5 < rawVoltage) {
            _monitor.rawVoltage = rawVoltage;
            update = true;
        }
    }
    if (update) {
        _monitor.percentageVoltage = map(_monitor.rawVoltage, minVoltage, maxVoltage);
    }
}

void Measurement::calculateFlow(monitor_t &_monitor) {
    byte rawFlow = getFlow();
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

byte Measurement::getFlow() {
    byte currentFlow = flowCount;
    flowCount = 0;
    if (currentFlow < minFlow) {
        return minFlow;
    }

    if (currentFlow > maxFlow) {
        return maxFlow;
    }

    return currentFlow;
}

void Measurement::countFlow() {
    flowCount++;
}

byte Measurement::map(double x, double in_min, double in_max) {
    return ((x - in_min) * 100) / (in_max - in_min);
}

void Measurement::updateBuzzer(bool state) {
    if (state) {
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }
}