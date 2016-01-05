#include <string.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include "sxbiff.h"

Window wu_create_window(Display *disp, int width, int height)
{
	int screen = DefaultScreen(disp);
	Window wind;
	Atom wm_delete_wind;
	XSizeHints *size;

	wind = XCreateSimpleWindow(disp, RootWindow(disp, screen), 0, 0,
		width, height, 0, BlackPixel(disp, screen), WhitePixel(disp, screen));

	if (!wind) {
		FATAL_ERROR("Could not create a window.", 1);
	}

	wm_delete_wind = XInternAtom(disp, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(disp, wind, &wm_delete_wind, 1);

	XSelectInput(disp, wind, StructureNotifyMask | ButtonPressMask |
		KeyPressMask);
	size = XAllocSizeHints();

	if (!size) {
		FATAL_ERROR("Could not allocate memory for size hints.", 1);
	}

	size->flags = PSize | PMinSize;
	size->width = size->min_width = size->max_width = SXBIFF_WIDTH;
	size->height = size->min_height = size->max_height = SXBIFF_HEIGHT;
	XSetWMNormalHints(disp, wind, size);
	XFree(size);

	XMapWindow(disp, wind);
	XFlush(disp);
	return wind;
}

void wu_set_window_above(Display *disp, Window wind)
{
	Atom wm_state, wm_state_above;
	XEvent event;

	if ((wm_state = XInternAtom(disp, "_NET_WM_STATE", False)) != None)
	{
		if ((wm_state_above = XInternAtom(disp, "_NET_WM_STATE_ABOVE", False))
			!= None)
		{
			event.xclient.type = ClientMessage;
			event.xclient.serial = 0;
			event.xclient.send_event = True;
			event.xclient.display = disp;
			event.xclient.window = wind;
			event.xclient.message_type = wm_state;
			event.xclient.format = 32;
			event.xclient.data.l[0] = 1; /* _NET_WM_STATE_ADD */
			event.xclient.data.l[1] = wm_state_above;
			event.xclient.data.l[2] = 0;
			event.xclient.data.l[3] = 0;
			event.xclient.data.l[4] = 0;

			if (!(XSendEvent(disp, DefaultRootWindow(disp), False,
				SubstructureRedirectMask | SubstructureNotifyMask, &event)))
			{
				FATAL_ERROR("Could not send an X event for window level.", -1);
			}
		}
		else
		{
			FATAL_ERROR("Could not access _NET_WM_STATE_ABOVE (EWMH?).", -1);
		}
	}
	else
	{
		FATAL_ERROR("Could not access _NET_WM_STATE (EWMH?).", -1);
	}
}

void wu_set_window_name(Display *disp, Window wind, unsigned char *name)
{
	XTextProperty prop;

	prop.value = name;
	prop.encoding = XA_STRING;
	prop.format = 8;
	prop.nitems = strlen(name);

	XSetWMName(disp, wind, &prop);
}

GC wu_create_gc(Display *disp, Window wind)
{
	int screen = DefaultScreen(disp);
	GC ctx;
	XGCValues values;

	ctx = XCreateGC(disp, wind, 0, &values);

	if (!ctx) {
		FATAL_ERROR("Could not create a graphics context.", 1);
	}

	XSetForeground(disp, ctx, BlackPixel(disp, screen));
	XSetBackground(disp, ctx, WhitePixel(disp, screen));
	XSetLineAttributes(disp, ctx, 2, LineSolid, CapButt, JoinBevel);
	XSetFillStyle(disp, ctx, FillSolid);

	return ctx;
}

Pixmap wu_create_bitmap(Display *disp, Window wind, char *bits, int width,
	int height)
{
	Pixmap bmp = XCreateBitmapFromData(disp, wind, bits, width, height);

	if (!bmp) {
		FATAL_ERROR("Could not create a bitmap.", 1);
	}

	return bmp;
}

void wu_render_bitmap(Display *disp, Window wind, Pixmap bmp)
{
	GC ctx = wu_create_gc(disp, wind);
	struct timespec sleep = { .tv_sec = 0, .tv_nsec = 125000 };

	int i;
	for (i = 0; i < 10; i++) {
		int j;
		for (j = 0; j < 10; j++) {
			XCopyPlane(disp, bmp, wind, ctx, 0, 0, SXBIFF_WIDTH, SXBIFF_HEIGHT,
				0, 0, 1);
			nanosleep(&sleep, NULL);
		}
	}

	XFlush(disp);

	XFreeGC(disp, ctx);
}
