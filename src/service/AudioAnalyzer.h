#ifndef __AUDIO_ANALYZER_H__
#define __AUDIO_ANALYZER_H__

#include <arduinoFFT.h>

typedef struct audio_state {
    unsigned int channel_sub_0HZ_20HZ;
    unsigned int channel_bass_20HZ_40HZ;
    unsigned int channel_bass_40HZ_80HZ;
    unsigned int channel_bass_80HZ_160HZ;
    unsigned int channel_mid_160HZ_300HZ;
    unsigned int channel_mid_300HZ_600HZ;
    unsigned int channel_mid_600HZ_1kHZ;
    unsigned int channel_treble_1kHZ_3kHZ;
    unsigned int channel_treble_3kHZ_5kHZ;
    unsigned int channel_treble_5kHZ_10kHZ;
    unsigned int channel_top_10kHZ_20kHZ;
} audio_state;

typedef struct audio_samples {
    double vReal[1024];
    double vImag[1024];
} audio_samples;

class AudioAnalyzer
{
    public:
        AudioAnalyzer (unsigned char audioPin);

        unsigned long getUpdateTime();
        audio_state getAudioState();

    private:
        const unsigned short int SAMPLES = 1024;             // Must be a power of 2
        const unsigned short int SAMPLING_FREQUENCY = 40000; // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
        const unsigned int SAMPLING_DURATION = round(1000000 * (1.0 / AudioAnalyzer::SAMPLING_FREQUENCY));
        const unsigned char LEVEL_TRESHOLD = 64;

        unsigned long updateTime = 0;
        unsigned char audioPin;

        arduinoFFT *FFT;
        audio_samples audioSamples;

        audio_samples makeAudioSamples();
        audio_samples transformAudioSamples(audio_samples audioSamples);
        audio_state makeAudioState(audio_samples audioSamples);
        unsigned int convertToChannelValue(double value);

};

#endif