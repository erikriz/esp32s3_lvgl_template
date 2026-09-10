#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/**
 * Generic placeholder UI — stands in for a SquareLine Studio export so the
 * project builds and runs before you have a real one. Re-exporting from
 * SquareLine into this folder (see README) overwrites this file; nothing
 * outside `ui/` depends on it being exactly this content, only on the
 * symbols below existing.
 *
 * It doubles as a smoke test for the display + touch BSP:
 *   - drag the arc  -> exercises touch tracking (and reveals a wrong
 *                      swap_xy/mirror_x/mirror_y touch calibration)
 *   - tap the button -> exercises touch taps + LVGL click events, and
 *                       flips the screen background color so it's obvious
 *                       even without reading the label
 */
void ui_init(void);

extern lv_obj_t *ui_scrMain;
extern lv_obj_t *ui_lblTitle;
extern lv_obj_t *ui_lblSubtitle;
extern lv_obj_t *ui_arcTest;
extern lv_obj_t *ui_lblArcValue;
extern lv_obj_t *ui_btnTap;
extern lv_obj_t *ui_lblTapCount;

#ifdef __cplusplus
}
#endif

#endif
