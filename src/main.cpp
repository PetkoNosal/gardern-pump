#include <Arduino.h>
#include "Objects.h"
#include "Measurement.h"
#include "Display.h"
#include "Encoder.h"
#include "Servos.h"

static update_t update = {true, true};
static state_t state = {false, false, false, false, false, 0, 0};
static monitor_t monitor = {0, 0};

static Display display;
static Encoder encoder;
static Servos servos;
static Measurement measurement;

void setup() {
//    Serial.begin(9600);
    display.init();
    encoder.init();
    measurement.init(monitor);
    servos.init();
}

void loop() {
    /* UPDATE STATES */
    encoder.checkActivity(update, state);
    measurement.updateReadings(update, state, monitor);

    /* ACT ON UPDATES */
    display.redrawDisplay(update, state, monitor);
    measurement.actOnChanges(update, state, monitor);
    servos.actOnChanges(update, state);
}
