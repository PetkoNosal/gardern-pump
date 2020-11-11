#include <Adafruit_SSD1306.h>
#include "Display.h"
#include "Bitmaps.h"

#define OLED_ADDRESS 0x3C

static Adafruit_SSD1306 display(128, 64, &Wire, -1);

void Display::init() {
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    display.setTextWrap(false);
    display.setTextColor(SSD1306_WHITE);
}

void Display::redrawDisplay(update_t &_update, state_t &_state, monitor_t &_monitor) {
    if (_update.display) {
        display.clearDisplay();
        drawAction(_state);
        drawOverlay(_state);
        drawConfig(_state, _monitor);
        drawStatic();
        display.display();
        _update.display = false;
    }
}

void Display::drawConfig(state_t &_state, monitor_t &_monitor) {
    byte curVolt = _monitor.percentageVoltage;
    byte curFlow = _monitor.percentageFlow;

    display.setCursor(23, 4);
    display.print(curVolt);
    display.print(F("%"));

    if (curFlow >= 100) {
        display.setCursor(82, 4);
    } else if (curFlow < 100 && curFlow > 9) {
        display.setCursor(88, 4);
    } else if (curFlow < 10) {
        display.setCursor(94, 4);
    }

    display.print(curFlow);
    display.print(F("%"));

    if (_state.motorSpeed == 100) {
        display.setCursor(51, 16);
    } else if (_state.motorSpeed < 100 && _state.motorSpeed > 9) {
        display.setCursor(55, 16);
    } else if (_state.motorSpeed < 10) {
        display.setCursor(59, 16);
    }

    display.print(_state.motorSpeed);
    display.print(F("%"));
}

void Display::drawAction(state_t &_state) {
    if (_state.valve_in_stream) {
        display.drawBitmap(15, 17, VALVE_ON_BMP, 25, 20, SSD1306_WHITE);
    } else {
        display.drawBitmap(15, 17, VALVE_OFF_BMP, 25, 20, SSD1306_WHITE);
    }
    if (_state.valve_in_barrel) {
        display.drawBitmap(15, 44, VALVE_ON_BMP, 25, 20, SSD1306_WHITE);
    } else {
        display.drawBitmap(15, 44, VALVE_OFF_BMP, 25, 20, SSD1306_WHITE);
    }
    if (_state.valve_out_barrel) {
        display.drawBitmap(86, 17, VALVE_ON_BMP, 25, 20, SSD1306_WHITE);
    } else {
        display.drawBitmap(86, 17, VALVE_OFF_BMP, 25, 20, SSD1306_WHITE);
    }
    if (_state.valve_out_hose) {
        display.drawBitmap(86, 44, VALVE_ON_BMP, 25, 20, SSD1306_WHITE);
    } else {
        display.drawBitmap(86, 44, VALVE_OFF_BMP, 25, 20, SSD1306_WHITE);
    }
    if (_state.pump) {
        display.drawBitmap(49, 25, PUMP_SELECTED_BMP, 28, 28, SSD1306_WHITE);
    } else {
        display.drawBitmap(49, 25, PUMP_UNSELECTED_BMP, 28, 28, SSD1306_WHITE);
    }
}

void Display::drawOverlay(state_t &_state) {
    if (_state.selected == 0) {
        display.drawRect(49, 26, 28, 28, SSD1306_WHITE);
    }
    if (_state.selected == 1) {
        display.drawRect(15, 17, 25, 20, SSD1306_WHITE);
    }
    if (_state.selected == 2) {
        display.drawRect(15, 44, 25, 20, SSD1306_WHITE);
    }
    if (_state.selected == 3) {
        display.drawRect(86, 17, 25, 20, SSD1306_WHITE);
    }
    if (_state.selected == 4) {
        display.drawRect(86, 44, 25, 20, SSD1306_WHITE);
    }
}

void Display::drawStatic() {
    display.drawBitmap(0, 17, STREAM_BMP, 10, 20, SSD1306_WHITE);
    display.drawBitmap(0, 44, BARREL_BMP, 10, 20, SSD1306_WHITE);
    display.drawBitmap(116, 17, BARREL_BMP, 10, 20, SSD1306_WHITE);
    display.drawBitmap(116, 44, DROPLET_BMP, 10, 20, SSD1306_WHITE);

    display.drawBitmap(0, 0, BATTERY_INFO, 20, 16, SSD1306_WHITE);
    display.drawBitmap(108, 0, FLOW_INFO, 20, 16, SSD1306_WHITE);

    display.drawRect(54, 59, 16, 3, SSD1306_WHITE);
    display.drawTriangle(
            73, 60,
            70, 57,
            70, 63, SSD1306_WHITE);
    display.drawTriangle(
            73, 60,
            71, 58,
            71, 62, SSD1306_WHITE);
    display.drawLine(55, 60, 73, 60, SSD1306_WHITE);

    display.drawLine(10, 27, 13, 27, SSD1306_WHITE);
    display.drawLine(11, 54, 13, 54, SSD1306_WHITE);
    display.drawLine(112, 27, 114, 27, SSD1306_WHITE);
    display.drawLine(112, 54, 114, 54, SSD1306_WHITE);

    display.drawLine(41, 27, 47, 40, SSD1306_WHITE);
    display.drawLine(41, 54, 47, 40, SSD1306_WHITE);
    display.drawLine(84, 54, 78, 40, SSD1306_WHITE);
    display.drawLine(84, 27, 78, 40, SSD1306_WHITE);
}