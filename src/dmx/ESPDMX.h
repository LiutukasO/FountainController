#ifndef ESPDMX_h
#define ESPDMX_h

#include <inttypes.h>

class DMXESPSerial {
public:
  static void init();
  void init(int MaxChan, int dmxPin);
  uint8_t read(int channel);

  // Update local buffer only — not yet on the DMX bus.
  void write(int channel, uint8_t value);

  // Copy local buffer into the esp_dmx driver (still not on the bus).
  void loadDriver();

  // loadDriver() + send frame on the DMX bus.
  void transmit();

  void end();
};

#endif
