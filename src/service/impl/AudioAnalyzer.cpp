
#include <service/AudioAnalyzer.h>

//#define IN_DEBUG_MODE


AudioAnalyzer::AudioAnalyzer (unsigned char audioPin){
  this->audioPin = audioPin;
  this->FFT = new arduinoFFT();
}


audio_samples AudioAnalyzer::makeAudioSamples(){
  unsigned long sampleStartedAt;
  audio_samples audioSamples;
  for (int i = 0; i < AudioAnalyzer::SAMPLES; i++) {
    sampleStartedAt = micros();
    audioSamples.vReal[i] = analogRead(this->audioPin); // Using Arduino ADC nomenclature. A conversion takes about 1uS on an ESP32
    audioSamples.vImag[i] = 0;
    while ((micros() - sampleStartedAt) < AudioAnalyzer::SAMPLING_DURATION) { /* do nothing to wait */ }
  }
  return audioSamples;
}


audio_samples AudioAnalyzer::transformAudioSamples(audio_samples audioSamples){
  this->FFT->Windowing(audioSamples.vReal, AudioAnalyzer::SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  this->FFT->Compute(audioSamples.vReal, audioSamples.vImag, AudioAnalyzer::SAMPLES, FFT_FORWARD);
  this->FFT->ComplexToMagnitude(audioSamples.vReal, audioSamples.vImag, AudioAnalyzer::SAMPLES);
  return audioSamples;
}


unsigned int AudioAnalyzer::convertToChannelValue(double value){
  unsigned int channelValue = (unsigned int)value;
  if (channelValue > AudioAnalyzer::LEVEL_TRESHOLD){
    channelValue = AudioAnalyzer::LEVEL_TRESHOLD;
  }
  return channelValue;
}

// TODO: Audio signal value mapping to channels
audio_state AudioAnalyzer::makeAudioState(audio_samples audioSamples){
  audio_state audioState;
  // Don't use sample 0 and only the first SAMPLES/2 are usable.
  for (int i = 2; i < (AudioAnalyzer::SAMPLES/2); i++){
    // Each array element represents a frequency and its value, is the amplitude.
    // Note the frequencies are not discrete.
    if (audioSamples.vReal[i] > 1500) { // Add a crude noise filter, 10 x amplitude or more
      unsigned int channelValue = convertToChannelValue(audioSamples.vReal[i]);
      if (i<=2 )             audioState.channel_sub_0HZ_20HZ      = channelValue; //   125Hz
      if (i >2   && i<=4 )   audioState.channel_bass_20HZ_40HZ    = channelValue; //   250Hz
      if (i >4   && i<=7 )   audioState.channel_bass_40HZ_80HZ    = channelValue; //   500Hz
      if (i >7   && i<=15 )  audioState.channel_bass_80HZ_160HZ   = channelValue; //  1000Hz
      if (i >15  && i<=40 )  audioState.channel_mid_160HZ_300HZ   = channelValue; //  2000Hz
      if (i >40  && i<=70 )  audioState.channel_mid_300HZ_600HZ   = channelValue; //  4000Hz
      if (i >70  && i<=288 ) audioState.channel_mid_600HZ_1kHZ    = channelValue; //  8000Hz
      if (i >70  && i<=288 ) audioState.channel_treble_1kHZ_3kHZ  = channelValue;
      if (i >70  && i<=288 ) audioState.channel_treble_3kHZ_5kHZ  = channelValue;
      if (i >70  && i<=288 ) audioState.channel_treble_5kHZ_10kHZ = channelValue;
      if (i >288           ) audioState.channel_top_10kHZ_20kHZ   = channelValue; // 16000Hz
    }
  }
  return audioState;
}


audio_state AudioAnalyzer::getAudioState(){
  this->updateTime = millis();
  audio_samples audioSamples = this->makeAudioSamples();
  audioSamples = this->transformAudioSamples(audioSamples);
  return this->makeAudioState(audioSamples);
}