#ifndef AUDIO_H
#define AUDIO_H

#include "AudioTools.h"
#include "AudioLibs/A2DPStream.h"

#define SPEAKER_NAME "ACTON II"

extern StreamCopy copier;
extern PitchShift pitchShifter;
void audio_init();

#endif