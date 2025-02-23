//
// Created by sebas on 30/12/2024.
//

#include "platform.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <cstdio>
#include <cstdlib>

static Display* display;
static Window window;
static GLXContext glContext;
static Atom wmDeleteMessage;

int platform_create_window(int width, int height, const char* title) {
    display = XOpenDisplay(nullptr);
    if (!display) {
        fprintf(stderr, "Failed to open X display\n");
        return EXIT_FAILURE;
    }

    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);

    XSetWindowAttributes swa;
    swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

    window = XCreateWindow(display, root, 0, 0, width, height, 0,
                           CopyFromParent, InputOutput, CopyFromParent,
                           CWEventMask, &swa);

    if (!window) {
        fprintf(stderr, "Failed to create X11 window\n");
        return EXIT_FAILURE;
    }

    XStoreName(display, window, title);
    XMapWindow(display, window);

    // Handle window close event
    wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    return EXIT_SUCCESS;
}

void platform_update_window() {
    XEvent event;
    while (XPending(display)) {
        XNextEvent(display, &event);
        if (event.type == ClientMessage &&
            (Atom)event.xclient.data.l[0] == wmDeleteMessage) {
            exit(EXIT_SUCCESS);
            }
    }
}
