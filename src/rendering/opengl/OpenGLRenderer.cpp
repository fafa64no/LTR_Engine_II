//
// Created by sebas on 02/01/2025.
//

#include "OpenGLRenderer.h"

#include "default_objects.h"
#include "glFunctions.h"
#include "platform.h"

#include "glm.hpp"
#include "log.h"



OpenGLRenderer::OpenGLRenderer() {
    this->resolution = platform_get_window_size();
    this->screenSize = platform_get_screen_size();

    load_gl_functions();
    this->initRenderingParameters();

    load_default_objects();

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);

    ltr_log_gl_info("renderer: ", renderer, ", vendor: ", vendor);

    this->initializing = false;
}

void OpenGLRenderer::render() {
    if (initializing) return;
    this->refreshRenderingParameters();
    this->preparePostProcessing();

    this->renderSkybox();
    this->renderWorld();
    this->renderPostProcessing();
    this->renderUI();
}



void OpenGLRenderer::initRenderingParameters() {
    auto gl_debug_callback = [](
        GLenum /*source*/,
        GLenum /*type*/,
        GLuint /*id*/,
        const GLenum severity,
        GLsizei /*length*/,
        const GLchar* message,
        const void* /*user*/
    ) -> void APIENTRY {
        if (
            severity == GL_DEBUG_SEVERITY_LOW ||
            severity == GL_DEBUG_SEVERITY_MEDIUM ||
            severity == GL_DEBUG_SEVERITY_HIGH
        ) {
            ltr_log_error(message);
        } else {
            ltr_log_gl_info(message);
        }
    };
    glDebugMessageCallback(gl_debug_callback,nullptr);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderer::refreshRenderingParameters() {
    glViewport(0, 0, resolution.x, resolution.y);
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void OpenGLRenderer::preparePostProcessing() {

}

// ReSharper disable once CppMemberFunctionMayBeStatic
void OpenGLRenderer::renderSkybox() {
    for (const auto shader : skybox_shaders)
        shader->renderObjects();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void OpenGLRenderer::renderWorld() {
    for (const auto shader : world_shaders)
        shader->renderObjects();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void OpenGLRenderer::renderPostProcessing() {
    for (const auto shader : postprocessing_shaders)
        shader->renderObjects();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void OpenGLRenderer::renderUI() {
    for (const auto shader : ui_shaders)
        shader->renderObjects();
}
