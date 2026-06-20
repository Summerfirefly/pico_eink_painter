#ifndef _EINK_PHOTO_INIT_H_
#define _EINK_PHOTO_INIT_H_

#include <stdbool.h>

bool eink_photo_init(void);

static bool epaper_pin_init(void);
static bool fatfs_init(void);

#endif // _EINK_PHOTO_INIT_H_
