#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT();

#define SAMPLES 1024             // Must be a power of 2
#define SAMPLING_FREQUENCY 40000 // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define amplitude 150            // Depending on your audio source level, you may need to increase this value

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

unsigned long newTime, oldTime;
int dominant_value;

void makeSamples(){
  for (int i = 0; i < SAMPLES; i++) {
    newTime = micros();
    vReal[i] = analogRead(A0); // Using Arduino ADC nomenclature. A conversion takes about 1uS on an ESP32
  //vReal[i] = analogRead(VP); // Using logical name fo ADC port
  //vReal[i] = analogRead(36); // Using pin number for ADC port
    vImag[i] = 0;
    while ((micros() - newTime) < sampling_period_us) { /* do nothing to wait */ }
  }
}

void transformSamples(){
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
}