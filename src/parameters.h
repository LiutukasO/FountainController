#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <parameters-wifi.h>

//#define IN_DEBUG_MODE

// RECEIVER DEMO: AC:67:B2:2B:0E:90
unsigned char receiverAddress[] = {0xAC, 0x67, 0xB2, 0x2B, 0x0E, 0x90};
// RECEIVER REAL: 08:3A:F2:52:D6:E0
//unsigned char receiverAddress[] = {0x08, 0x3A, 0xF2, 0x52, 0xD6, 0xE0};

// SENDER DEMO: 10:52:1C:68:0B:8C
unsigned char senderAddress[] = {0x10, 0x52, 0x1C, 0x68, 0x0B, 0x8C};

bool isValidSender(const uint8_t *mac) {
  if (mac[0] == 0x98 && mac[1] == 0x41 && mac[2] == 0x5C && mac[3] == 0x03 && mac[4] == 0xF2 && mac[5] == 0xAF) return true;
  if (mac[0] == 0x10 && mac[1] == 0x52 && mac[2] == 0x1C && mac[3] == 0x68 && mac[4] == 0x0B && mac[5] == 0x8C) return true;
  if (mac[0] == 0xAC && mac[1] == 0x67 && mac[2] == 0xB2 && mac[3] == 0x2B && mac[4] == 0x0E && mac[5] == 0x70) return true;
  return false;
}

unsigned char valveChannelGroup = 1; // +4 channels

// CENTER
unsigned char led1ChannelGroup  = 5; // +3 channels

// MIDDLE
unsigned char led2ChannelGroup  = 8; // +3 channels

// EXTERNAL
unsigned char led3ChannelGroup  = 11; // +3 channels
unsigned char led4ChannelGroup  = 14; // +3 channels

unsigned long iddleTimeToDemo = 1000; // 1s
unsigned long demoUpdateInterval = 3000; // 3s

unsigned char audioInputPin = 35; //14;


#endif