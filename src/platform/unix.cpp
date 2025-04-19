//
// Created by sebas on 30/12/2024.
//

#include <cstring>
#include <mouseInputs.h>

#include "platform.h"

#include "log.h"

#include <X11/Xlib.h>
#include <GL/glx.h>

#include "keys.h"

bool isMouseHidden = false;
bool isMouseLocked = false;

glm::ivec2 currentWindowSize;
glm::vec2 currentMousePos;

Display* display;
Window window;
PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT_ptr;

Atom wmDeleteWindow;

void* platform_load_gl_function(const char* funName) {
    const auto proc = (void*) glXGetProcAddressARB(reinterpret_cast<const GLubyte *>(funName));
    if (!proc) {
        ltr_log_fatal("Failed to load : ", funName);
        return nullptr;
    }
    return proc;
}

int platform_create_window(const char* title) {
    return platform_create_window(platform_get_screen_size().x, platform_get_screen_size().y, title);
}

int platform_create_window(const int width, const int height, const char* title) {
    currentWindowSize.x = width;
    currentWindowSize.y = height;

    display = XOpenDisplay(nullptr);
    if (!display) {
        display = XOpenDisplay(nullptr);
        ltr_log_fatal("platform_create_window: Failed to get display");
        return EXIT_FAILURE;
    }
    window = XCreateSimpleWindow(
        display,
        DefaultRootWindow(display),
        0,         // xPos
        0,         // yPos
        width,
        height,
        0,         // border width
        0,         // border
        0          // background
    );

    //window = XCreateWindow(
    //    display,
    //
    //);

    constexpr int pixelAttribs[]{
        GLX_RGBA,           True, ///TODO check if works on raspberry
        GLX_DOUBLEBUFFER,   True,
        GLX_RED_SIZE,          8,
        GLX_GREEN_SIZE,        8,
        GLX_BLUE_SIZE,         8,
        None
    };

    int fbcCount = 0;
    const GLXFBConfig* fbc = glXChooseFBConfig(
        display,
        DefaultScreen(display),
        pixelAttribs,
        &fbcCount
    );
    if (!fbc) {
        ltr_log_fatal("platform_create_window: Failed to create GLX framebuffer config");
        return EXIT_FAILURE;
    }

    const auto glXCreateContextAttribsARB = reinterpret_cast<PFNGLXCREATECONTEXTATTRIBSARBPROC>(
        glXGetProcAddress(reinterpret_cast<const GLubyte *>("glXCreateContextAttribsARB"))
    );
    glXSwapIntervalEXT_ptr = reinterpret_cast<PFNGLXSWAPINTERVALEXTPROC>(
        glXGetProcAddress(reinterpret_cast<const GLubyte *>("glXSwapIntervalEXT"))
    );

    constexpr int contextAttribs[]{
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 3,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
        None
    };

    GLXContext context = glXCreateContextAttribsARB(
        display,
        fbc[0],
        nullptr,
        true,
        contextAttribs
    );

    constexpr long event_mask =
        ExposureMask
        | KeyPressMask
        | KeyReleaseMask
        | ButtonPressMask
        | ButtonReleaseMask;
    XSelectInput(display, window, event_mask);

    XMapWindow(display, window);
    glXMakeCurrent(display, window, context);

    wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteWindow, 1);

    return EXIT_SUCCESS;
}

glm::ivec2 platform_get_window_size() { return currentWindowSize; }

glm::ivec2 platform_get_screen_size() {
    Display* disp = XOpenDisplay(nullptr);
    Screen* screen = DefaultScreenOfDisplay(disp);
    return {screen->width, screen->height};
}

glm::vec2 platform_get_mouse_position() { return currentMousePos; }

void platform_update_window() {
    Window root;
    Window child;
    glm::ivec2 mouse_pos;
    glm::ivec2 root_pos;
    unsigned int mask_return;

    XQueryPointer(
        display,
        window,
        &root,
        &child,
        &root_pos.x,
        &root_pos.y,
        &mouse_pos.x,
        &mouse_pos.y,
        &mask_return
    );
    currentMousePos = glm::vec2(
        static_cast<float>(mouse_pos.x) / static_cast<float>(currentWindowSize.x),
        static_cast<float>(mouse_pos.y) / static_cast<float>(currentWindowSize.y)
    );

    while (XPending(display)) {
        XEvent event;
        XNextEvent(display, &event);

        switch(event.type) {
            case Expose: {
                currentWindowSize.x = event.xexpose.width;
                currentWindowSize.y = event.xexpose.height;
                break;
            }
            case KeyPress:
            case KeyRelease: {
                const KeyCodeID keyCode = KeyCodeLookupTable[event.xkey.keycode];
                update_key(keyCode, event.type == KeyPress);
                break;
            }
            case ButtonPress: {
                switch(event.xbutton.button) {
                    case Button1:
                        leftClickDown(currentMousePos);
                    break;
                    case Button2:
                        middleClickDown(currentMousePos);
                    break;
                    default:
                        rightClickDown(currentMousePos);
                }
                break;
            }
            case ButtonRelease: {
                switch(event.xbutton.button) {
                    case Button1:
                        leftClickUp(currentMousePos);
                        break;
                    case Button2:
                        middleClickUp(currentMousePos);
                        break;
                    default:
                        rightClickUp(currentMousePos);
                }
                break;
            }
            case ClientMessage: {
                if (
                    const Atom wmProtocol = XInternAtom(display, "WM_PROTOCOLS", False);
                    event.xclient.message_type == wmProtocol &&
                    event.xclient.data.l[0] == wmDeleteWindow
                ) {
                    // Window close event
                    exit(EXIT_SUCCESS);
                }
            }
            default:
                break;
        }
    }
}

void platform_swap_buffers() {
    glXSwapBuffers(display, window);
}

void lockMouse()    { isMouseLocked = true; ltr_log_warn("lockMouse: Function not yet implemented on UNIX"); }
void unlockMouse()  { isMouseLocked = false; ltr_log_warn("unlockMouse: Function not yet implemented on UNIX"); }
void hideMouse()    { isMouseHidden = true; ltr_log_warn("hideMouse: Function not yet implemented on UNIX"); }
void showMouse()    { isMouseHidden = false; ltr_log_warn("showMouse: Function not yet implemented on UNIX"); }

void platform_fill_keycode_lookup_table() {
    // A - Z
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_A)] = KEY_A;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_B)] = KEY_B;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_C)] = KEY_C;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_D)] = KEY_D;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_E)] = KEY_E;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F)] = KEY_F;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_G)] = KEY_G;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_H)] = KEY_H_;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_I)] = KEY_I;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_J)] = KEY_J;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_K)] = KEY_K;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_L)] = KEY_L;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_M)] = KEY_M;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_N)] = KEY_N;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_O)] = KEY_O;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_P)] = KEY_P;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Q)] = KEY_Q;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_R)] = KEY_R;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_S)] = KEY_S;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_T)] = KEY_T;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_U)] = KEY_U;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_V)] = KEY_V;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_W)] = KEY_W;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_X)] = KEY_X;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Y)] = KEY_Y;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Z)] = KEY_Z;

    // a - z
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_a)] = KEY_A;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_b)] = KEY_B;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_c)] = KEY_C;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_d)] = KEY_D;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_e)] = KEY_E;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_f)] = KEY_F;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_g)] = KEY_G;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_h)] = KEY_H_;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_i)] = KEY_I;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_j)] = KEY_J;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_k)] = KEY_K;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_l)] = KEY_L;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_m)] = KEY_M;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_n)] = KEY_N;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_o)] = KEY_O;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_p)] = KEY_P;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_q)] = KEY_Q;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_r)] = KEY_R;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_s)] = KEY_S;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_t)] = KEY_T;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_u)] = KEY_U;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_v)] = KEY_V;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_w)] = KEY_W;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_x)] = KEY_X;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_y)] = KEY_Y;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_z)] = KEY_Z;

    KeyCodeLookupTable[XKeysymToKeycode(display, XK_0)] = KEY_0;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_1)] = KEY_1;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_2)] = KEY_2;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_3)] = KEY_3;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_4)] = KEY_4;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_5)] = KEY_5;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_6)] = KEY_6;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_7)] = KEY_7;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_8)] = KEY_8;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_9)] = KEY_9;

    KeyCodeLookupTable[XKeysymToKeycode(display, XK_space)] = KEY_SPACE;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_grave)] = KEY_TICK;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_minus)] = KEY_MINUS;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_equal)] = KEY_EQUAL;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_bracketleft)] = KEY_LEFT_BRACKET;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_bracketright)] = KEY_RIGHT_BRACKET;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_semicolon)] = KEY_SEMICOLON;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_quotedbl)] = KEY_QUOTE;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_comma)] = KEY_COMMA;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_period)] = KEY_PERIOD;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_slash)] = KEY_FORWARD_SLASH;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_backslash)] = KEY_BACKWARD_SLASH;

    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Tab)] = KEY_TAB;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Escape)] = KEY_ESCAPE;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Pause)] = KEY_PAUSE;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Up)] = KEY_UP;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Down)] = KEY_DOWN;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Left)] = KEY_LEFT;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Right)] = KEY_RIGHT;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_BackSpace)] = KEY_BACKSPACE;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Return)] = KEY_RETURN;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Delete)] = KEY_DELETE;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Insert)] = KEY_INSERT;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Home)] = KEY_HOME;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_End)] = KEY_END;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Page_Up)] = KEY_PAGE_UP;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Page_Down)] = KEY_PAGE_DOWN;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Caps_Lock)] = KEY_CAPS_LOCK;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Num_Lock)] = KEY_NUM_LOCK;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Scroll_Lock)] = KEY_SCROLL_LOCK;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Menu)] = KEY_MENU;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Shift_L)] = KEY_SHIFT;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Shift_R)] = KEY_SHIFT;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Control_L)] = KEY_CONTROL;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Control_R)] = KEY_CONTROL;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Alt_L)] = KEY_ALT;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_Alt_R)] = KEY_ALT;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F1)] = KEY_F1;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F2)] = KEY_F2;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F3)] = KEY_F3;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F4)] = KEY_F4;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F5)] = KEY_F5;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F6)] = KEY_F6;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F7)] = KEY_F7;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F8)] = KEY_F8;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F9)] = KEY_F9;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F10)] = KEY_F10;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F11)] = KEY_F11;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_F12)] = KEY_F12;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_0)] = KEY_NUMPAD_0;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_1)] = KEY_NUMPAD_1;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_2)] = KEY_NUMPAD_2;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_3)] = KEY_NUMPAD_3;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_4)] = KEY_NUMPAD_4;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_5)] = KEY_NUMPAD_5;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_6)] = KEY_NUMPAD_6;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_7)] = KEY_NUMPAD_7;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_8)] = KEY_NUMPAD_8;
    KeyCodeLookupTable[XKeysymToKeycode(display, XK_KP_9)] = KEY_NUMPAD_9;
}