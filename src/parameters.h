#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <parameters-wifi.h>

//#define IN_DEBUG_MODE

//Receiver: ac:67:b2:2b:0e:70
//Receiver: 10:52:1C:68:03:90 (bad)
//Receiver: AC:67:B2:2B:0E:90 (old)
//Receiver: 08:3A:F2:52:D6:E0 (real)
//Sender: 10:52:1C:68:0B:8C
//Sender: 98:41:5c:03:f2:af
unsigned char receiverAddress[] = {0x08, 0x3A, 0xF2, 0x52, 0xD6, 0xE0};
unsigned char senderAddress[] = {0x10, 0x52, 0x1C, 0x68, 0x0B, 0x8C};

bool isValidSender(const uint8_t *mac) {
  if (mac[0] == 0x98 && mac[1] == 0x41 && mac[2] == 0x5C && mac[3] == 0x03 && mac[4] == 0xF2 && mac[5] == 0xAF) return true;
  if (mac[0] == 0x10 && mac[1] == 0x52 && mac[2] == 0x1C && mac[3] == 0x68 && mac[4] == 0x0B && mac[5] == 0x8C) return true;
  if (mac[0] == 0xAC && mac[1] == 0x67 && mac[2] == 0xB2 && mac[3] == 0x2B && mac[4] == 0x0E && mac[5] == 0x70) return true;
  return false;
}

unsigned char valveChannelGroup = 1; //17;

// CENTER
unsigned char led1ChannelGroup  = 25; //5;

// MIDDLE
unsigned char led2ChannelGroup  = 17;

// EXTERNAL
unsigned char led3ChannelGroup  = 9;
unsigned char led4ChannelGroup  = 13;

unsigned long iddleTimeToDemo = 10000; // 10s
unsigned long demoUpdateInterval = 1000; // 1s

unsigned char audioInputPin = 14;


#endif