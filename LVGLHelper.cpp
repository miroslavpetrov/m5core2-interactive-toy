#include "LVGLHelper.h"
#include <esp_timer.h>
#include "audio.h"
constexpr int32_t HOR_RES=320;
constexpr int32_t VER_RES=240;

lv_display_t *display;
lv_indev_t *indev;


void my_display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  lv_draw_sw_rgb565_swap(px_map, w * h);
  M5.Display.pushImageDMA<uint16_t>(area->x1, area->y1, w, h, (uint16_t *)px_map);
  lv_disp_flush_ready(disp);
}
uint32_t my_tick_function() {
  return (esp_timer_get_time() / 1000LL);
}
void my_touchpad_read(lv_indev_t *drv, lv_indev_data_t *data) {
  M5.update();
  auto count = M5.Touch.getCount();

  if (count == 0) {
    data->state = LV_INDEV_STATE_RELEASED;
  } else {
    auto touch = M5.Touch.getDetail(0);
    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = touch.x;
    data->point.y = touch.y;
  }
}
static void m_button_cb(lv_event_t * event)
{
    Serial.println("Mickey Mouse");
    pitchShifter.setActive(0);
    pitchShifter.setValue(1.2);
    pitchShifter.setActive(1);
}

static void h_button_cb(lv_event_t * event)
{
    Serial.println("Hulk");
    pitchShifter.setActive(0);
    pitchShifter.setValue(0.8);
    pitchShifter.setActive(1);
}

void lvgl_init() {
  lv_init();

  lv_tick_set_cb(my_tick_function);

  display = lv_display_create(HOR_RES, VER_RES);
  lv_display_set_flush_cb(display, my_display_flush);

  static lv_color_t buf1[HOR_RES * 1]; //reduced to excange FPS for clear audio
  lv_display_set_buffers(display, buf1, nullptr, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

  indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);

  lv_indev_set_read_cb(indev, my_touchpad_read);

  
  lv_obj_t *screen = lv_obj_create(lv_screen_active());
  lv_obj_set_size(screen, 320, 240);

  static lv_coord_t col_dsc[] = { 290, LV_GRID_TEMPLATE_LAST };
  static lv_coord_t row_dsc[] = { 210, LV_GRID_TEMPLATE_LAST };

  lv_obj_t *grid = lv_obj_create(lv_screen_active());

  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

  lv_obj_set_size(grid, 320, 240);

  lv_obj_center(grid);

  lv_obj_t *obj;

  obj = lv_obj_create(grid);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
                       LV_GRID_ALIGN_STRETCH, 0, 1);

  LV_IMG_DECLARE(m_button);
  LV_IMG_DECLARE(h_button);

  static lv_style_prop_t tr_prop[] = { LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_IMAGE_RECOLOR_OPA, 0 };
  static lv_style_transition_dsc_t tr;

  static lv_style_t style_def;
  lv_style_init(&style_def);
  lv_style_set_text_color(&style_def, lv_color_white());

  static lv_style_t style_pr;
  lv_style_init(&style_pr);
  lv_style_set_image_recolor_opa(&style_pr, LV_OPA_30);
  lv_style_set_image_recolor(&style_pr, lv_color_black());

  lv_obj_t *img_btn_key = lv_imagebutton_create(obj);
  lv_imagebutton_set_src(img_btn_key, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &m_button, NULL);
  lv_obj_add_style(img_btn_key, &style_def, 0);
  lv_obj_add_style(img_btn_key, &style_pr, LV_STATE_PRESSED);
  lv_obj_align(img_btn_key, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_add_event_cb(img_btn_key, m_button_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *img_btn_key2 = lv_imagebutton_create(obj);
  lv_imagebutton_set_src(img_btn_key2, LV_IMAGEBUTTON_STATE_RELEASED, NULL, &h_button, NULL);
  lv_obj_add_style(img_btn_key2, &style_def, 0);
  lv_obj_add_style(img_btn_key2, &style_pr, LV_STATE_PRESSED);
  lv_obj_align(img_btn_key2, LV_ALIGN_RIGHT_MID, 0, 0);
  lv_obj_add_event_cb(img_btn_key2, h_button_cb, LV_EVENT_CLICKED, NULL);
}

