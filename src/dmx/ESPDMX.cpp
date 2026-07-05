#include <Arduino.h>
#include <string.h>

#include <dmx/ESPDMX.h>
#include <esp_dmx.h>

//#define IN_DEBUG_MODE
//#define DMX_TRACE  // print channels 1-16 on each transmit()

// Hardware wiring (receiver ESP32 → RS485 → Decoder512):
//   GPIO4  → DI
//   DE+RE  → 3.3V (always transmit; not GPIO-controlled)
//   RO     → not connected
//   RS485 A → connector pin 2, B → pin 3, GND → pin 1
static bool dmxStarted = false;
static int tx_pin = 4;
static uint8_t dmxData[DMX_PACKET_SIZE] = {};

static void traceDmxFrame() {
#if defined(DMX_TRACE)
  Serial.print("DMX TX ch 1-");
  Serial.print("16");
  Serial.print(": ");
  for (unsigned char channel = 1; channel <= 16; channel++) {
    Serial.printf("%3u", dmxData[channel]);
    if (channel < 16) {
      Serial.print(' ');
    }
  }
  Serial.println();
#endif
}

static void installDriver() {
  if (dmxStarted) {
    return;
  }

  dmx_config_t config = DMX_CONFIG_DEFAULT;
  dmx_personality_t personalities[] = {
    {1, "Default Personality"}
  };

  dmx_driver_install(DMX_NUM_1, &config, personalities, 1);
  dmx_set_pin(DMX_NUM_1, tx_pin, DMX_PIN_NO_CHANGE, DMX_PIN_NO_CHANGE);
  memset(dmxData, 0, sizeof(dmxData));
  dmxData[0] = 0;  // DMX start code
  dmxStarted = true;

  Serial.printf("DMX: TX=GPIO%d (DE/RE hardwired)\n", tx_pin);
}

void DMXESPSerial::init() {
#ifdef IN_DEBUG_MODE
  Serial.printf("\n\t\tDMX->init()");
#endif
  installDriver();
}

void DMXESPSerial::init(int channels, int dmxPin) {
  tx_pin = dmxPin;
  (void)channels;
  installDriver();
}

uint8_t DMXESPSerial::read(int channel) {
  if (dmxStarted == false) init();

  if (channel < 1) channel = 1;
  if (channel >= DMX_PACKET_SIZE) channel = DMX_PACKET_SIZE - 1;
  return dmxData[channel];
}

void DMXESPSerial::write(int channel, uint8_t value) {
#ifdef IN_DEBUG_MODE
  Serial.printf("\n\t\tDMX->write(%d, %d)", channel, value);
#endif
  if (dmxStarted == false) init();

  if (channel < 1) channel = 1;
  if (channel >= DMX_PACKET_SIZE) channel = DMX_PACKET_SIZE - 1;

  dmxData[channel] = value;
}

void DMXESPSerial::loadDriver() {
  if (dmxStarted == false) init();

  dmx_write(DMX_NUM_1, dmxData, DMX_PACKET_SIZE);
}

void DMXESPSerial::transmit() {
  if (dmxStarted == false) init();

  loadDriver();
  dmx_send_num(DMX_NUM_1, DMX_PACKET_SIZE);
  dmx_wait_sent(DMX_NUM_1, DMX_TIMEOUT_TICK);
  traceDmxFrame();
}

void DMXESPSerial::end() {
  if (dmxStarted) {
    dmx_driver_delete(DMX_NUM_1);
  }
  dmxStarted = false;
}
