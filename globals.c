#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdbool.h>

Display *display;
Window sxbiff_window;
bool up;
Pixmap flagup, flagdown;
