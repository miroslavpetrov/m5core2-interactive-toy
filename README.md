# M5Stack Core2 Interactive Toy
An interactive toy that changes the pitch of the user's voice and streams it over Bluetooth A2DP

![img](https://github.com/miroslavpetrov/m5core2-interactive-toy/assets/25277610/32fe8bbe-cf02-439d-bd79-90cdc3d54dd6)

## Project description

When I was little I had this parrot toy which repeated my words with a funny voice. I have great memories playing with this toy and I have decied to create a similar one for my kids. 

The project uses M5Stack Core2, [LVGL 9](https://github.com/lvgl/lvgl) for UI, [arduino-audio-tools](https://github.com/pschatzmann/arduino-audio-tools) for sound processing and [ESP32 A2DP](https://github.com/pschatzmann/ESP32-A2DP) for streaming.

## How to connect to a Bluetooth speaker?
Currently the name of the speaker is hardcoded in the audio.h file - ```#define SPEAKER_NAME "ACTON II"```
Once the device boots, press the pair button on the Bluetooth speaker and the 

## Generating character images

The character images were created using Photoshop and exported as transparent PNG. 
After that using the [LVGL 9 image convertor tool](https://lvgl.io/tools/imageconverter_v9), the PNGs were converted to a C Array with RGB565A8 color format to maintain their rounded corners.

## How voice change works?

The voice is changed by manipulating the pitch of the sound input using the PitchShift class of arduino-audio-tools. The pitch is adjustable using the pitchShifter.setValue() method. Pitch above 1.0 generates a Mickey Mouse-like voice and pitch below 1.0 generates a Hulk-like vocie.

## Further improvements

- The allocation of resources needs a bit more fine tuning because there is a sligthly audiable buffer underflow in the output sound.
- Currently, name of the Blueooth receiver is hardcoded. It would be a good idea to implement a GUI for searching and selecting the desired Blueooth receiver.
- Add a battery indicator.

## Credits
- [LVGL](https://github.com/lvgl/lvgl)
- [Arduino-Audio-Tools](https://github.com/pschatzmann/arduino-audio-tools)
- [ESP32 A2DP](https://github.com/pschatzmann/ESP32-A2DP)

