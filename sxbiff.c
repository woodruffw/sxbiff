#include "sxbiff.h"

void sxbiff(Display *disp)
{
	Window wind;
	GC ctx;
	Pixmap flagup, flagdown;

	wind = wu_create_window(disp, SXBIFF_WIDTH, SXBIFF_HEIGHT);
	ctx = wu_create_gc(disp, wind);
	flagup = wc_create_bitmap(disp, window, flagup_bits, flagup_width,
			flagup_height);
	flagdown = wc_create_bitmap(disp, window, flagdown_bits, flagdown_width,
			flagdown_height);

	/* always start with the flag down */
	wu_render_bitmap(disp, wind, flagdown);

	while (1) {
		XNextEvent(disp, &evt);
	}

	/* cleanup */
	XFreePixmap(disp, flagup);
	XFreePixmap(disp, flagdown);
	XFreeGC(disp, ctx);
	XDestroyWindow(disp, wind);
}
