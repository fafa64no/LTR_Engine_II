//
// Created by sebas on 23/02/2025.
//

#ifndef PLATFORM_HEADER_H
#define PLATFORM_HEADER_H

#ifdef _WIN32
#include <windows.h>
#include "glcorearb.h"
#elif __linux__

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef GLAPI
#define GLAPI extern
#endif

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif

#ifndef GLX_GLXEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "glcorearb.h"

#include <GL/glx.h>
#include <GL/glxext.h>
#endif

#endif //PLATFORM_HEADER_H
