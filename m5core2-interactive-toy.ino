#include <Arduino.h>
#include <M5Unified.h>
#include <lvgl.h>
#include <esp_timer.h>
#include "LVGLHelper.h"
#include "audio.h"

TaskHandle_t audioTask;

void fAudioTask(void* pvParameters) {

  audio_init();

  for (;;) {
    //Copy data to A2DP
    copier.copy();
  }
}

void setup() {
  // LVGL runs on Core1 with Arduino Core, Audio runs at Core 0
  M5.begin();
  lvgl_init();
  xTaskCreatePinnedToCore(fAudioTask, "Task1", 5000, NULL, 15, &audioTask, 0);
}


void loop() {
  // Handle UI and touch input
  lv_task_handler();
  vTaskDelay(1);
}