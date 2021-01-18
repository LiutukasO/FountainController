#ifndef __FONTAIN_H__
#define __FONTAIN_H__

#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverAddress[] = {0x10, 0x52, 0x1C, 0x68, 0x03, 0x90};
uint8_t senderAddress[] = {0x10, 0x52, 0x1C, 0x68, 0x09, 0x94};

typedef struct fountain_state
{
  unsigned long int valves;
  unsigned long int leds;
} fountain_state;


void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t espStatus)
{
  Serial.print("Packet Send Status:\t");
  Serial.println(espStatus == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void printFountainState(fountain_state fountainState){
  Serial.print("\tvalves: "); Serial.println(fountainState.valves, BIN);
  Serial.print("\tleds:   "); Serial.println(fountainState.leds, BIN);
}


#endif