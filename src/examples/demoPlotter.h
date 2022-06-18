
#include <Arduino.h>
#include "Plotter.h"

#define CHANNEL 13
const double samplingFrequency = 100; //Hz, must be less than 10000 due to ADC
unsigned int sampling_period_us;
unsigned long sampleTime = 0;

double x;

Plotter plotter;

void setup()
{
  sampling_period_us = round(1000000*(1.0/samplingFrequency));
  plotter.Begin();
  plotter.AddTimeGraph( "Some title of a graph", 500, "label for x", x );
}

void loop()
{
  while(sampleTime + sampling_period_us > micros()) return;
  sampleTime = micros();
  x = analogRead(CHANNEL);
  plotter.Plot();
}

