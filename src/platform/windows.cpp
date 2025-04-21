//
// Created by sebas on 30/12/2024.
//

#include "platform.h"
#include "log.h"
#include <cstdio>

#include <windows.h>
#include "glad.h"
#include "glfw3.h"

#include "mouseInputs.h"
#include "keys.h"


extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; // NVIDIA
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;   // AMD
}

static HWND window;
static HDC dc;
static BOOL isMouseHidden = FALSE;
static BOOL isMouseLocked = FALSE;

static glm::ivec2 currentWindowSize;


void* platform_load_gl_function(const char* funName){
    PROC proc = wglGetProcAddress(funName);
    if (!proc){
        static HMODULE openglDLL=LoadLibraryA((LPCSTR)"opengl32.dll");
        proc = GetProcAddress(openglDLL,funName);
        if (!proc){
            ltr_log_fatal("Failed to load : ", funName);
            return nullptr;
        }
    }
    return (void*) proc;
}

LRESULT CALLBACK windows_window_callback(HWND curWindow, UINT msg, WPARAM wParam, LPARAM lParam){
    LRESULT result=0;
    switch (msg){
        case WM_CLOSE:{
            exit(EXIT_SUCCESS);
            break;
        }
        case WM_SIZE:{
            RECT rect={};
            GetClientRect(curWindow,&rect);
            currentWindowSize.x = rect.right - rect.left;
            currentWindowSize.y = rect.bottom - rect.top;
            break;
        }
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:{
            const bool isDown = (msg == WM_KEYDOWN) || (msg == WM_SYSKEYDOWN) ||
                    (msg == WM_LBUTTONDOWN);
            const KeyCodeID keyCode = KeyCodeLookupTable[wParam];
            update_key(keyCode, isDown);
            break;
        }
        case WM_LBUTTONDOWN:{
            POINT point = {};
            GetCursorPos(&point);
            const auto pos = glm::vec2(
                (float)point.x/(float)currentWindowSize.x,
                (float)point.y/(float)currentWindowSize.y
            );
            leftClickDown(pos);
            break;
        }
        case WM_RBUTTONDOWN:{
            POINT point = {};
            GetCursorPos(&point);
            const auto pos = glm::vec2(
                (float)point.x/(float)currentWindowSize.x,
                (float)point.y/(float)currentWindowSize.y
            );
            rightClickDown(pos);
            break;
        }
        case WM_MBUTTONDOWN:{
            POINT point = {};
            GetCursorPos(&point);
            const auto pos = glm::vec2(
                (float)point.x/(float)currentWindowSize.x,
                (float)point.y/(float)currentWindowSize.y
            );
            middleClickDown(pos);
            break;
        }
        case WM_LBUTTONUP:{
            POINT point = {};
            GetCursorPos(&point);
            const auto pos = glm::vec2(
                (float)point.x/(float)currentWindowSize.x,
                (float)point.y/(float)currentWindowSize.y
            );
            leftClickUp(pos);
            break;
        }
        case WM_RBUTTONUP:{
            POINT point = {};
            GetCursorPos(&point);
            const auto pos = glm::vec2(
                (float)point.x/(float)currentWindowSize.x,
                (float)point.y/(float)currentWindowSize.y
            );
            rightClickUp(pos);
            break;
        }
        case WM_MBUTTONUP:{
            POINT point = {};
            GetCursorPos(&point);
            const auto pos = glm::vec2(
                (float)point.x/(float)currentWindowSize.x,
                (float)point.y/(float)currentWindowSize.y
            );
            middleClickUp(pos);
            break;
        }
        default:{
            result = DefWindowProcA(curWindow, msg, wParam, lParam);
        }
    }
    return result;
}

int platform_create_window(const char* title) {
    return platform_create_window(platform_get_screen_size().x, platform_get_screen_size().y, title);
}

int platform_create_window(int width, int height, const char* title){
    ltr_log_debug("Creating window");

    ltr_log_debug("Finished creating window");
    return EXIT_SUCCESS;
}

glm::ivec2 platform_get_window_size() {
    return currentWindowSize;
}

glm::ivec2 platform_get_screen_size() {
    return {1920, 1080};
}

glm::vec2 platform_get_mouse_position() {
    POINT point = {};
    GetCursorPos(&point);
    const auto pos = glm::vec2(
        static_cast<float>(point.x) / static_cast<float>(currentWindowSize.x),
        static_cast<float>(point.y) / static_cast<float>(currentWindowSize.y)
    );
    return pos;
}

void platform_update_window() {
    //Gather input
    MSG msg;
    while (PeekMessageA(&msg,window,0,0,PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    //Mouse Visibility
    POINT point = {};
    GetCursorPos(&point);
    ScreenToClient(window,&point);
    if (isMouseHidden) {
        while(ShowCursor(true) <= 0);
    }
}

void platform_swap_buffers() {
    SwapBuffers(dc);
}

void lockMouse() {
    isMouseLocked=TRUE;
}
void unlockMouse() {
    isMouseLocked=FALSE;
}
void hideMouse() {
    isMouseHidden=TRUE;
}
void showMouse() {
    isMouseHidden=FALSE;
}

void platform_fill_keycode_lookup_table() {
    KeyCodeLookupTable[VK_LBUTTON] = KEY_MOUSE_LEFT;
    KeyCodeLookupTable[VK_MBUTTON] = KEY_MOUSE_MIDDLE;
    KeyCodeLookupTable[VK_RBUTTON] = KEY_MOUSE_RIGHT;

    KeyCodeLookupTable['A'] = KEY_A;
    KeyCodeLookupTable['B'] = KEY_B;
    KeyCodeLookupTable['C'] = KEY_C;
    KeyCodeLookupTable['D'] = KEY_D;
    KeyCodeLookupTable['E'] = KEY_E;
    KeyCodeLookupTable['F'] = KEY_F;
    KeyCodeLookupTable['G'] = KEY_G;
    KeyCodeLookupTable['H'] = KEY_H_;
    KeyCodeLookupTable['I'] = KEY_I;
    KeyCodeLookupTable['J'] = KEY_J;
    KeyCodeLookupTable['K'] = KEY_K;
    KeyCodeLookupTable['L'] = KEY_L;
    KeyCodeLookupTable['M'] = KEY_M;
    KeyCodeLookupTable['N'] = KEY_N;
    KeyCodeLookupTable['O'] = KEY_O;
    KeyCodeLookupTable['P'] = KEY_P;
    KeyCodeLookupTable['Q'] = KEY_Q;
    KeyCodeLookupTable['R'] = KEY_R;
    KeyCodeLookupTable['S'] = KEY_S;
    KeyCodeLookupTable['T'] = KEY_T;
    KeyCodeLookupTable['U'] = KEY_U;
    KeyCodeLookupTable['V'] = KEY_V;
    KeyCodeLookupTable['W'] = KEY_W;
    KeyCodeLookupTable['X'] = KEY_X;
    KeyCodeLookupTable['Y'] = KEY_Y;
    KeyCodeLookupTable['Z'] = KEY_Z;
    KeyCodeLookupTable['0'] = KEY_0;
    KeyCodeLookupTable['1'] = KEY_1;
    KeyCodeLookupTable['2'] = KEY_2;
    KeyCodeLookupTable['3'] = KEY_3;
    KeyCodeLookupTable['4'] = KEY_4;
    KeyCodeLookupTable['5'] = KEY_5;
    KeyCodeLookupTable['6'] = KEY_6;
    KeyCodeLookupTable['7'] = KEY_7;
    KeyCodeLookupTable['8'] = KEY_8;
    KeyCodeLookupTable['9'] = KEY_9;

    KeyCodeLookupTable[VK_SPACE] = KEY_SPACE,
    KeyCodeLookupTable[VK_OEM_3] = KEY_TICK,
    KeyCodeLookupTable[VK_OEM_MINUS] = KEY_MINUS,

    KeyCodeLookupTable[VK_OEM_PLUS] = KEY_EQUAL,
    KeyCodeLookupTable[VK_OEM_4] = KEY_LEFT_BRACKET,
    KeyCodeLookupTable[VK_OEM_6] = KEY_RIGHT_BRACKET,
    KeyCodeLookupTable[VK_OEM_1] = KEY_SEMICOLON,
    KeyCodeLookupTable[VK_OEM_7] = KEY_QUOTE,
    KeyCodeLookupTable[VK_OEM_COMMA] = KEY_COMMA,
    KeyCodeLookupTable[VK_OEM_PERIOD] = KEY_PERIOD,
    KeyCodeLookupTable[VK_OEM_2] = KEY_FORWARD_SLASH,
    KeyCodeLookupTable[VK_OEM_5] = KEY_BACKWARD_SLASH,
    KeyCodeLookupTable[VK_TAB] = KEY_TAB,
    KeyCodeLookupTable[VK_ESCAPE] = KEY_ESCAPE,
    KeyCodeLookupTable[VK_PAUSE] = KEY_PAUSE,
    KeyCodeLookupTable[VK_UP] = KEY_UP,
    KeyCodeLookupTable[VK_DOWN] = KEY_DOWN,
    KeyCodeLookupTable[VK_LEFT] = KEY_LEFT,
    KeyCodeLookupTable[VK_RIGHT] = KEY_RIGHT,
    KeyCodeLookupTable[VK_BACK] = KEY_BACKSPACE,
    KeyCodeLookupTable[VK_RETURN] = KEY_RETURN,
    KeyCodeLookupTable[VK_DELETE] = KEY_DELETE,
    KeyCodeLookupTable[VK_INSERT] = KEY_INSERT,
    KeyCodeLookupTable[VK_HOME] = KEY_HOME,
    KeyCodeLookupTable[VK_END] = KEY_END,
    KeyCodeLookupTable[VK_PRIOR] = KEY_PAGE_UP,
    KeyCodeLookupTable[VK_NEXT] = KEY_PAGE_DOWN,
    KeyCodeLookupTable[VK_CAPITAL] = KEY_CAPS_LOCK,
    KeyCodeLookupTable[VK_NUMLOCK] = KEY_NUM_LOCK,
    KeyCodeLookupTable[VK_SCROLL] = KEY_SCROLL_LOCK,
    KeyCodeLookupTable[VK_APPS] = KEY_MENU,

    KeyCodeLookupTable[VK_SHIFT] = KEY_SHIFT,
    KeyCodeLookupTable[VK_LSHIFT] = KEY_SHIFT,
    KeyCodeLookupTable[VK_RSHIFT] = KEY_SHIFT,

    KeyCodeLookupTable[VK_CONTROL] = KEY_CONTROL,
    KeyCodeLookupTable[VK_LCONTROL] = KEY_CONTROL,
    KeyCodeLookupTable[VK_RCONTROL] = KEY_CONTROL,

    KeyCodeLookupTable[VK_MENU] = KEY_ALT,
    KeyCodeLookupTable[VK_LMENU] = KEY_ALT,
    KeyCodeLookupTable[VK_RMENU] = KEY_ALT,

    KeyCodeLookupTable[VK_F1] = KEY_F1;
    KeyCodeLookupTable[VK_F2] = KEY_F2;
    KeyCodeLookupTable[VK_F3] = KEY_F3;
    KeyCodeLookupTable[VK_F4] = KEY_F4;
    KeyCodeLookupTable[VK_F5] = KEY_F5;
    KeyCodeLookupTable[VK_F6] = KEY_F6;
    KeyCodeLookupTable[VK_F7] = KEY_F7;
    KeyCodeLookupTable[VK_F8] = KEY_F8;
    KeyCodeLookupTable[VK_F9] = KEY_F9;
    KeyCodeLookupTable[VK_F10] = KEY_F10;
    KeyCodeLookupTable[VK_F11] = KEY_F11;
    KeyCodeLookupTable[VK_F12] = KEY_F12;

    KeyCodeLookupTable[VK_NUMPAD0] = KEY_NUMPAD_0;
    KeyCodeLookupTable[VK_NUMPAD1] = KEY_NUMPAD_1;
    KeyCodeLookupTable[VK_NUMPAD2] = KEY_NUMPAD_2;
    KeyCodeLookupTable[VK_NUMPAD3] = KEY_NUMPAD_3;
    KeyCodeLookupTable[VK_NUMPAD4] = KEY_NUMPAD_4;
    KeyCodeLookupTable[VK_NUMPAD5] = KEY_NUMPAD_5;
    KeyCodeLookupTable[VK_NUMPAD6] = KEY_NUMPAD_6;
    KeyCodeLookupTable[VK_NUMPAD7] = KEY_NUMPAD_7;
    KeyCodeLookupTable[VK_NUMPAD8] = KEY_NUMPAD_8;
    KeyCodeLookupTable[VK_NUMPAD9] = KEY_NUMPAD_9;
}