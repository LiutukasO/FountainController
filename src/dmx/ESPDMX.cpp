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
#include <HardwareSerial.h>
#include "driver/uart.h"

//#define IN_DEBUG_MODE

#define dmxMaxChannel  512
#define defaultMax 32

#define DMXSPEED       250000
#define DMXFORMAT      SERIAL_8N2
#define BREAKSPEED     83333
#define BREAKFORMAT    SERIAL_8N1

bool dmxStarted = false;
int sendPin = 4; //17;		//dafault on ESP32
int receivePin = 16;

//DMX value array and size. Entry 0 will hold startbyte
uint8_t dmxData[dmxMaxChannel] = {};
int channelSize;

HardwareSerial DMXSerial(2);

void DMXESPSerial::init() {
  channelSize = defaultMax;

  DMXSerial.begin(DMXSPEED, DMXFORMAT, receivePin, sendPin);
  pinMode(sendPin, OUTPUT);
  dmxStarted = true;
}

// Set up the DMX-Protocol
void DMXESPSerial::init(int channels, int dmxPin) {
  sendPin = dmxPin;

  if (channels > dmxMaxChannel || channels <= 0) {
    channels = defaultMax;
  }

  channelSize = channels;

  DMXSerial.begin(DMXSPEED, DMXFORMAT, receivePin, sendPin);
  pinMode(sendPin, OUTPUT);
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
}

void DMXESPSerial::end() {
  delete dmxData;
  channelSize = 0;
  DMXSerial.end();
  dmxStarted = false;
}


/*
void DMXESPSerial::update() {
  if (dmxStarted == false) init();

//Send break
  digitalWrite(sendPin, HIGH);
  DMXSerial.begin(BREAKSPEED, BREAKFORMAT, receivePin, sendPin);
  DMXSerial.write(0);
  DMXSerial.flush();
  delay(1);
  DMXSerial.end();

  //send data
  DMXSerial.begin(DMXSPEED, DMXFORMAT, receivePin, sendPin);
  digitalWrite(sendPin, LOW);
  DMXSerial.write(dmxData, channelSize);
  DMXSerial.flush();
  delay(1);
  DMXSerial.end();
}
*/

void DMXESPSerial::update() {
  if (dmxStarted == false) init();

  //Send break
  DMXSerial.changeBaud(BREAKSPEED, BREAKFORMAT);
  // send the break as a "slow" byte
  DMXSerial.write(0);
  delayMicroseconds(88);
  
  // switch back to the original baud rate
  DMXSerial.changeBaud(DMXSPEED, DMXFORMAT);
  // For the dimmers the start byte goes from first element of dmxData array
  // Send dmx Data
  DMXSerial.write(dmxData, channelSize+1);
  DMXSerial.flush();
}

// Function to update the DMX bus
