#include <Arduino.h>
#include <ADCSampler.h>

ADCSampler *adcSampler = NULL;

// replace this with your machines IP Address
#define ADC_SERVER_URL "http://192.168.1.71:5003/adc_samples"

// i2s config for using the internal ADC
i2s_config_t adcI2SConfig = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
    .sample_rate = 32000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0};

// how many samples to read at once
const int SAMPLE_SIZE = 16384;

/*
// send data to a remote address
void sendData(WiFiClient *wifiClient, HTTPClient *httpClient, const char *url, uint8_t *bytes, size_t count)
{
  // send them off to the server
  digitalWrite(2, HIGH);
  httpClient->begin(*wifiClient, url);
  httpClient->addHeader("content-type", "application/octet-stream");
  httpClient->POST(bytes, count);
  httpClient->end();
  digitalWrite(2, LOW);
}
*/

// Task to write samples from ADC to our server
void adcWriterTask(void *param)
{
  I2SSampler *sampler = (I2SSampler *)param;
  int16_t *samples = (int16_t *)malloc(sizeof(uint16_t) * SAMPLE_SIZE);
  if (!samples)
  {
    Serial.println("Failed to allocate memory for samples");
    return;
  }
  while (true)
  {
    int samples_read = sampler->read(samples, SAMPLE_SIZE);
    //sendData(wifiClientADC, httpClientADC, ADC_SERVER_URL, (uint8_t *)samples, samples_read * sizeof(uint16_t));
  }
}


void setup()
{
  Serial.begin(115200);

  // input from analog microphones such as the MAX9814 or MAX4466
  // internal analog to digital converter sampling using i2s
  // create our samplers
  adcSampler = new ADCSampler(ADC_UNIT_1, ADC1_CHANNEL_7, adcI2SConfig);

  // set up the adc sample writer task
  TaskHandle_t adcWriterTaskHandle;
  adcSampler->start();
  xTaskCreatePinnedToCore(adcWriterTask, "ADC Writer Task", 4096, adcSampler, 1, &adcWriterTaskHandle, 1);
}

void loop()
{
  // nothing to do here - everything is taken care of by tasks
}