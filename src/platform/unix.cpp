//
// Created by sebas on 30/12/2024.
//

#include "platform.h"

#include <platform_header.h>
#include <log.h>

static Display* display;
static Window window;
static GLXContext glContext;
static Atom wmDeleteMessage;

static bool isMouseHidden = false;
static bool isMouseLocked = false;

void* platform_load_gl_function(char* funName) {
    auto proc = reinterpret_cast<void*>(glXGetProcAddressARB(reinterpret_cast<const GLubyte *>(funName)));
    if (!proc) {
        ltr_log_error("Failed to load OpenGL function: ", funName);
        return nullptr;
    }
    return proc;
}

int platform_create_window(int width, int height, const char* title) {
    display = XOpenDisplay(nullptr);
    if (!display) {
        ltr_log_error("Failed to open X display");
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
        ltr_log_error("Failed to create X11 window");
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
            ltr_log_info("Window close requested");
            exit(EXIT_SUCCESS);
            }
    }
}

void platform_swap_buffers() {
    glXSwapBuffers(display, window);
}

glm::ivec2 platform_get_window_size() {
    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, window, &windowAttributes);
    return {windowAttributes.width, windowAttributes.height};
}

glm::vec2 platform_get_mouse_position() {
    Window root, child;
    int rootX, rootY, winX, winY;
    unsigned int mask;
    bool result = XQueryPointer(display, window, &root, &child, &rootX, &rootY, &winX, &winY, &mask);

    if (!result) {
        ltr_log_error("Failed to get mouse position");
        return {-1.0f, -1.0f};  // Return invalid position on failure
    }

    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, window, &windowAttributes);

    // Normalize coordinates to [0, 1] range
    return {
        static_cast<float>(winX) / static_cast<float>(windowAttributes.width),
        static_cast<float>(winY) / static_cast<float>(windowAttributes.height)
    };
}

void lockMouse() {
    isMouseLocked = true;
}
void unlockMouse() {
    isMouseLocked = false;
}
void hideMouse() {
    isMouseHidden = true;
}
void showMouse() {
    isMouseHidden = false;
}

void platform_fill_keycode_lookup_table() {}