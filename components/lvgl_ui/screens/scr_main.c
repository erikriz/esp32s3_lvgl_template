#include "scr_main.h"
#include "screens.h"
#include "ui.h"             /* access Squareline widget objects (e.g. ui_lblTitle) */
#include "esp_log.h"

static const char *TAG = "scr_main";

/* ------------------------------------------------------------------ */
/* Persistent event callbacks — registered in prepare(), survive screen
 * transitions because they are attached to the widget, not the screen. */
/* ------------------------------------------------------------------ */

static uint32_t s_tap_count = 0;

static void on_arc_value_changed(lv_event_t *e)
{
    (void)e;
    int32_t value = lv_arc_get_value(ui_arcTest);
    lv_label_set_text_fmt(ui_lblArcValue, "%d", (int)value);
}

static void on_btn_tap_clicked(lv_event_t *e)
{
    (void)e;
    s_tap_count++;
    lv_label_set_text_fmt(ui_lblTapCount, "Toques: %u", (unsigned)s_tap_count);

    /* Flip the background between two colors on every tap — a working
     * touch panel is obvious at a glance, even without reading the label. */
    lv_color_t color = (s_tap_count % 2 == 0) ? lv_palette_main(LV_PALETTE_BLUE_GREY)
                                               : lv_palette_main(LV_PALETTE_TEAL);
    lv_obj_set_style_bg_color(ui_scrMain, color, 0);
}

/* ------------------------------------------------------------------ */

void scr_main_prepare(void)
{
    /* Register callbacks on widgets that must stay active across screens. */
    lv_obj_add_event_cb(ui_arcTest, on_arc_value_changed, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_btnTap, on_btn_tap_clicked, LV_EVENT_CLICKED, NULL);
    ESP_LOGD(TAG, "prepare");
}

void scr_main_init(void)
{
    /* Called every time the main screen becomes active.
     * Refresh dynamic content, restart animations, etc.
     */
    ESP_LOGD(TAG, "init");
}

void scr_main_uninit(void)
{
    /* Called when leaving the main screen.
     * Stop any screen-local timers or animations here.
     */
    ESP_LOGD(TAG, "uninit");
}

void scr_main_step(void)
{
    /* Called every ~20 ms while the main screen is active.
     * Poll sensors, update progress bars, handle encoder deltas, etc.
     * Keep this function fast — avoid blocking calls.
     */
}
