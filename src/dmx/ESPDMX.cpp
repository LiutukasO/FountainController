// - - - - -
// ESPDMX - A Arduino library for sending and receiving DMX using the builtin serial hardware port.
// ESPDMX.cpp: Library implementation file
//
// Copyright (C) 2015  Rick <ricardogg95@gmail.com>
// This work is licensed under a GNU style license.
//
// Last change: Marcel Seerig <https://github.com/mseerig>
//
// Documentation and samples are available at https://github.com/Rickgg/ESP-Dmx
// - - - - -

/* ----- LIBRARIES ----- */
#include <Arduino.h>

#include <dmx/ESPDMX.h>
#include <esp_dmx.h>

//#define IN_DEBUG_MODE

#define dmxMaxChannel  512
#define defaultMax 32

bool dmxStarted = false;
int transmitPin = 4; //17;		//dafault on ESP32
int receivePin = 16;
int enablePin = 21;
dmx_port_t dmxPort = 1;

//DMX value array and size. Entry 0 will hold startbyte
uint8_t dmxData[defaultMax] = {};
int channelSize;

void DMXESPSerial::init() {
  #ifdef IN_DEBUG_MODE
      Serial.printf("\n\t\tDMX->init()");
  #endif
  channelSize = defaultMax;

  dmx_config_t dmxConfig = DMX_DEFAULT_CONFIG;
  dmx_param_config(dmxPort, &dmxConfig);
  dmx_set_pin(dmxPort, transmitPin, receivePin, enablePin);

  int queueSize = 0;
  int interruptPriority = 1;
  dmx_driver_install(dmxPort, DMX_MAX_PACKET_SIZE, queueSize, NULL, interruptPriority);
  dmx_set_mode(dmxPort, DMX_MODE_WRITE);
  dmxData[0] = 0;

  //pinMode(transmitPin, OUTPUT);
  dmxStarted = true;
}

// Set up the DMX-Protocol
void DMXESPSerial::init(int channels, int dmxPin) {
  transmitPin = dmxPin;

  if (channels > dmxMaxChannel || channels <= 0) {
    channels = defaultMax;
  }

  channelSize = channels;

  init();

  //pinMode(sendPin, OUTPUT);
  dmxStarted = true;
}

// Function to read DMX data
uint8_t DMXESPSerial::read(int channel) {
  if (dmxStarted == false) init();

  if (channel < 1) channel = 1;
  if (channel > dmxMaxChannel) channel = dmxMaxChannel;
  return(dmxData[channel]);
}

// Function to send DMX data
void DMXESPSerial::write(int channel, uint8_t value) {
  #ifdef IN_DEBUG_MODE
      Serial.printf("\n\t\tDMX->write(%d, %d)", channel, value);
  #endif
  if (dmxStarted == false) init();

  if (channel < 1) channel = 1;
  if (channel > channelSize) channel = channelSize;

  dmxData[channel] = value;
  dmx_write_packet(dmxPort, dmxData, channelSize);  
}

void DMXESPSerial::update() {
  if (dmxStarted == false) init();

  dmx_send_packet(dmxPort, channelSize);
  dmx_wait_send_done(dmxPort, DMX_PACKET_TIMEOUT_TICK);
}

void DMXESPSerial::end() {
  delete dmxData;
  channelSize = 0;
  dmxStarted = false;
}

// Function to update the DMX bus
