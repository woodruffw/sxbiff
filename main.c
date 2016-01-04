#include <stdlib.h>

#include "sxbiff.h"

int main(int argc, char **argv)
{
	Display *disp;

	if (!(disp = XOpenDisplay(NULL))) {
		FATAL_ERROR("Could not connect to the X server.", 1);
	}

	sxbiff(disp);

	/* cleanup */
	XCloseDisplay(disp);

	return EXIT_SUCCESS;
}
