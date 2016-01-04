#include <stdbool.h>

#include "sxbiff.h"

void sxbiff(Display *disp)
{
	struct sigaction act = { .sa_handler = sigcatch };
	bool up = false;
	Window wind = wu_create_window(disp, SXBIFF_WIDTH, SXBIFF_HEIGHT);
	Pixmap flagup = wu_create_bitmap(disp, wind, flagup_bits, flagup_width,
			flagup_height);
	Pixmap flagdown = wu_create_bitmap(disp, wind, flagdown_bits, flagdown_width,
			flagdown_height);

	if (sigaction(SIGUSR1, &act, 0) < 0 || sigaction(SIGUSR2, &act, 0) < 0) {
		FATAL_ERROR("Could not set signal handler or handlers.", 1);
	}

	/* always start with the flag down */
	wu_render_bitmap(disp, wind, flagdown);

	while (1) {
		XEvent evt;
		XNextEvent(disp, &evt);

		switch (evt.type) {
			KeySym key;
			char buf[255];

			case KeyPress:
				if (XLookupString(&evt.xkey, buf, 255, &key, 0)) {
					if (buf[0] == 'q') {
						goto cleanup;
					}
				}
				break;
			case ButtonPress:
				if (evt.xbutton.button == Button1 && up) {
					wu_render_bitmap(disp, wind, flagdown);
					up = false;
				}
				break;
			default:
				break;
		}
	}

	cleanup:
	XFreePixmap(disp, flagup);
	XFreePixmap(disp, flagdown);
	XDestroyWindow(disp, wind);
}

void sigcatch(int sig)
{
	if (sig == SIGUSR1) {

	}
	else {

	}
}
