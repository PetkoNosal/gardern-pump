#include <Arduino.h>

static const unsigned char PROGMEM DROPLET_BMP[] =
    {0x0c, 0x00, 0x0c, 0x00, 0x1e, 0x00, 0x12, 0x00, 0x12, 0x00, 0x33, 0x00, 0x21, 0x00, 0x61, 0x80,
     0x40, 0x80, 0xc0, 0xc0, 0x80, 0x40, 0x80, 0x40, 0x80, 0x40, 0x81, 0x40, 0x83, 0x40, 0x86, 0x40,
     0xcc, 0xc0, 0x61, 0x80, 0x33, 0x00, 0x1e, 0x00};

static const unsigned char PROGMEM BARREL_BMP[] =
    {0xff, 0xc0, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80,
     0x40, 0x80, 0x40, 0x80, 0xff, 0xc0, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80, 0xff, 0xc0, 0x40, 0x80,
     0x40, 0x80, 0x40, 0x80, 0x40, 0x80, 0xff, 0xc0};

static const unsigned char PROGMEM STREAM_BMP[] =
    {0x00, 0x00, 0x00, 0x00, 0x92, 0x00, 0x49, 0x00, 0x24, 0x80, 0x24, 0x80, 0x24, 0x80, 0x24, 0x80,
     0x49, 0x00, 0x92, 0x00, 0x92, 0x00, 0x49, 0x00, 0x24, 0x80, 0x24, 0x80, 0x24, 0x80, 0x24, 0x80,
     0x49, 0x00, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00};

static const unsigned char PROGMEM VALVE_ON_BMP[] =
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf1, 0x54, 0x00, 0x01, 0x13, 0xfe, 0x00,
     0x07, 0xff, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00,
     0x3d, 0x10, 0x1e, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x3f, 0x16, 0xfe, 0x00,
     0x3b, 0x52, 0xee, 0x00, 0x3b, 0x54, 0xee, 0x00, 0x3f, 0x16, 0xfe, 0x00, 0x3f, 0xff, 0xfe, 0x00,
     0x3f, 0xff, 0xfe, 0x00, 0x3c, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const unsigned char PROGMEM VALVE_OFF_BMP[] =
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf1, 0x54, 0x00, 0x01, 0x13, 0xfe, 0x00,
     0x07, 0xff, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00,
     0x3d, 0x10, 0x1e, 0x00, 0x27, 0x1f, 0xf2, 0x00, 0x20, 0x00, 0x02, 0x00, 0x21, 0xdd, 0xc2, 0x00,
     0x25, 0x51, 0x12, 0x00, 0x25, 0x59, 0x92, 0x00, 0x21, 0xd1, 0x02, 0x00, 0x20, 0x00, 0x02, 0x00,
     0x27, 0xff, 0xf2, 0x00, 0x3c, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const unsigned char PROGMEM PUMP_UNSELECTED_BMP[] =
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x1f, 0x80, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x48, 0x20, 0x00, 0x28, 0x90, 0x91, 0x40,
     0x3f, 0x09, 0x4f, 0xc0, 0x28, 0x06, 0x01, 0x40, 0x2a, 0x06, 0x05, 0x40, 0x28, 0x06, 0x01, 0x40,
     0x3f, 0x29, 0x0f, 0xc0, 0x28, 0x90, 0x91, 0x40, 0x00, 0x41, 0x20, 0x00, 0x00, 0x20, 0x40, 0x00,
     0x00, 0x1f, 0x80, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x26, 0x40, 0x00, 0x00, 0x40, 0x20, 0x00,
     0x00, 0x86, 0x10, 0x00, 0x00, 0xb9, 0xd0, 0x00, 0x00, 0x80, 0x10, 0x00, 0x00, 0xbf, 0xd0, 0x00,
     0x00, 0x80, 0x10, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const unsigned char PROGMEM PUMP_SELECTED_BMP[] =
    {0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0,
     0xff, 0xe0, 0x7f, 0xf0, 0xff, 0xdf, 0xbf, 0xf0, 0xff, 0xb7, 0xdf, 0xf0, 0xd7, 0x6f, 0x6e, 0xb0,
     0xc0, 0xf6, 0xb0, 0x30, 0xd7, 0xf9, 0xfe, 0xb0, 0xd5, 0xf9, 0xfa, 0xb0, 0xd7, 0xf9, 0xfe, 0xb0,
     0xc0, 0xd6, 0xf0, 0x30, 0xd7, 0x6f, 0x6e, 0xb0, 0xff, 0xbe, 0xdf, 0xf0, 0xff, 0xdf, 0xbf, 0xf0,
     0xff, 0xe0, 0x7f, 0xf0, 0xff, 0xef, 0x7f, 0xf0, 0xff, 0xd9, 0xbf, 0xf0, 0xff, 0xbf, 0xdf, 0xf0,
     0xff, 0x79, 0xef, 0xf0, 0xff, 0x46, 0x2f, 0xf0, 0xff, 0x7f, 0xef, 0xf0, 0xff, 0x40, 0x2f, 0xf0,
     0xff, 0x7f, 0xef, 0xf0, 0xff, 0x00, 0x0f, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0};

static const unsigned char PROGMEM BATTERY_INFO[] =
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x9f, 0x00, 0x08, 0x91, 0x00, 0x7f, 0xff, 0xe0, 0x40,
     0x00, 0x20, 0x42, 0x00, 0x20, 0x42, 0x00, 0x20, 0x4f, 0x9f, 0x20, 0x42, 0x00, 0x20, 0x42, 0x00,
     0x20, 0x40, 0x00, 0x20, 0x40, 0x00, 0x20, 0x40, 0x00, 0x20, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x00};

static const unsigned char PROGMEM FLOW_INFO[] =
    {0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x06, 0x06, 0x00, 0x19, 0x81, 0x80, 0x12, 0x04, 0x80, 0x21,
     0x0a, 0x40, 0x40, 0x92, 0x20, 0x40, 0x60, 0x20, 0x40, 0x60, 0x20, 0x44, 0x90, 0x20, 0x25, 0x08,
     0x40, 0x22, 0x04, 0x80, 0x18, 0x19, 0x80, 0x06, 0x06, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00};
