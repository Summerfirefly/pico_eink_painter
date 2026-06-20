#ifndef _EINK_PHOTO_H_
#define _EINK_PHOTO_H_

#include <pico/time.h>

bool photo_change_timer_callback(repeating_timer_t *rt);
void pick_next_photo(void);
void show_photo(void);

static void scan_photo(void);

#endif // _EINK_PHOTO_H_
