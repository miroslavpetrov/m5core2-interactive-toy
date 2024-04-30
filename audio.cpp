#include "audio.h"

I2SStream i2s;          
A2DPStream a2dpStream;

float shift = 1.0;

// Set I2S mic as input for effects
AudioEffectStream effects(i2s);

PitchShift pitchShifter(shift, 1000);

// Copy data from effects to a2dp
StreamCopy copier(a2dpStream, effects);  


void audio_init() {
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // Start I2S input from mic
  Serial.println("starting I2S...");
  a2dpStream.addNotifyAudioChange(i2s);  
  auto cfg = i2s.defaultConfig(RX_MODE);
  cfg.signal_type = PDM;
  cfg.i2s_format = I2S_STD_FORMAT;
  cfg.channels = 2;  
  cfg.sample_rate = 44100;
  cfg.bits_per_sample = 16;
  cfg.is_master = true;
  cfg.port_no = 0;
  cfg.pin_bck = 12;
  cfg.pin_ws = 0;
  cfg.pin_data = 34;
  i2s.begin(cfg);

  // Apply effects
  effects.addEffect(pitchShifter);
  effects.begin(cfg);  

  // Start bluetooth
  Serial.println("starting A2DP...");
  auto cfgA2DP = a2dpStream.defaultConfig(TX_MODE);
  cfgA2DP.name = "ACTON II";
  a2dpStream.begin(cfgA2DP);

  // Set intial volume
  a2dpStream.setVolume(1.0);
}

