#ifndef AUDIO_H
#define AUDIO_H

#include "AudioTools.h"
#include "AudioLibs/A2DPStream.h"

extern StreamCopy copier;
extern PitchShift pitchShifter;
void audio_init();

#endif