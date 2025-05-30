//
// Created by sebas on 30/12/2024.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include "glm.hpp"

void* platform_load_gl_function(const char* funName);

int platform_create_window(const char* title);
int platform_create_window(int width, int height, const char* title);
void platform_update_window();
void platform_swap_buffers();
glm::ivec2 platform_get_window_size();
glm::ivec2 platform_get_screen_size();
glm::vec2 platform_get_mouse_position();

void lockMouse();
void unlockMouse();
void hideMouse();
void showMouse();

void platform_fill_keycode_lookup_table();

#endif //PLATFORM_H
