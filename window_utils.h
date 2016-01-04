#ifndef WINDOW_UTILS_H
#define WINDOW_UTILS_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

Window wu_create_window(Display *disp, int width, int height);
void wu_set_window_name(Display *disp, Window wind, unsigned char *name);
GC wu_create_gc(Display *disp, Window wind);
Pixmap wu_create_bitmap(Display *disp, Window wind, char *bits, int width,
	int height);
void wu_render_bitmap(Display *disp, Window wind, Pixmap bmp);

#endif
