//
// Created by simon on 13/04/25.
//

#ifndef PLATFORM_OPENGL_HEADER_H
#define PLATFORM_OPENGL_HEADER_H

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif

#ifdef WIN32
#include <windows.h>
#include "glcorearb.h"
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#endif //PLATFORM_OPENGL_HEADER_H
