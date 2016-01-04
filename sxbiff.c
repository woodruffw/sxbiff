#include <signal.h>

#include "sxbiff.h"
#include "window_utils.h"
#include "globals.h"

#include "flagup.xbm"
#include "flagdown.xbm"

static void sigcatch(int sig);

void sxbiff()
{
	bool exiting = false;
	struct sigaction act = { .sa_handler = sigcatch };

	up = false;
	sxbiff_window = wu_create_window(display, SXBIFF_WIDTH, SXBIFF_HEIGHT);
	wu_set_window_name(display, sxbiff_window, "sxbiff");
	flagup = wu_create_bitmap(display, sxbiff_window, flagup_bits, flagup_width,
			flagup_height);
	flagdown = wu_create_bitmap(display, sxbiff_window, flagdown_bits,
			flagdown_width, flagdown_height);

	if (sigaction(SIGUSR1, &act, 0) < 0 || sigaction(SIGUSR2, &act, 0) < 0) {
		FATAL_ERROR("Could not set signal handler(s).", 1);
	}

	/* always start with the flag down */
	wu_render_bitmap(display, sxbiff_window, flagdown);

	while (!exiting) {
		XEvent evt;
		XNextEvent(display, &evt);

		switch (evt.type) {
			KeySym key;
			char buf[255];

			case ConfigureNotify:
				if (up)	{
					wu_render_bitmap(display, sxbiff_window, flagup);
				}
				else {
					wu_render_bitmap(display, sxbiff_window, flagdown);
				}
				break;
			case KeyPress:
				if (XLookupString(&evt.xkey, buf, 255, &key, 0)) {
					if (buf[0] == 'q') {
						exiting = true;
					}
				}
				break;
			case ClientMessage:
				if (evt.xclient.data.l[0] == XInternAtom(display,
					"WM_DELETE_WINDOW", False)) {
					exiting = true;
				}
			case ButtonPress:
				if (evt.xbutton.button == Button1 && up) {
					wu_render_bitmap(display, sxbiff_window, flagdown);
					up = false;
				}
				break;
			default:
				break;
		}
	}

	XFreePixmap(display, flagup);
	XFreePixmap(display, flagdown);
	XDestroyWindow(display, sxbiff_window);
}

static void sigcatch(int sig)
{
	if (sig == SIGUSR1 && !up) {
		wu_render_bitmap(display, sxbiff_window, flagup);
		up = true;
	}
	else if (sig == SIGUSR2 && up) {
		wu_render_bitmap(display, sxbiff_window, flagdown);
		up = false;
	}
}
