//
// Created by sebas on 02/01/2025.
//

#include "OpenGLRenderer.h"

#include "glFunctions.h"
#include "platform.h"

#include "log.h"
#include "RenderEngine.h"
#include "shaders.h"
#include "vaos.h"
#include "textures.h"
#include "uiElements.h"

#include "glm.hpp"
/*
static GLuint
    frameBuffer,
    renderBuffer;


void glInit() {
    maxResolution = RenderEngine::getMaxWindowSize();
    load_gl_functions();
    glInitCfg();
    initShaders();
    loadTextures();
    initVAOs();
    initUIElements();
    glInitFrameBuffers();
}

void glInitCfg() {
    glDebugMessageCallback(&gl_debug_callback,nullptr);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void glInitFrameBuffers() {
    ltr_log_info("OpenGL Rendering Init Frame Buffer");
    // Frame Buffer
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    frameTexture->useAsTarget();
    ltr_log_info("OpenGL Rendering Init Render Buffer");
    // Render Buffer
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,maxResolution.x,maxResolution.y);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        renderBuffer
    );
    ltr_log_info("OpenGL Rendering Init Check");
    FATAL_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,"Scene framebuffer incomplete");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void glClearScreen() {
    glClearColor(0.8,0.8,0.8,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glRender() {
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glClearScreen();
    glEnable(GL_DEPTH_TEST);
    glRenderUI();
}

void glRenderUI() {
    for (auto* sprite : ui_sprites) {
        if (sprite == nullptr) continue;
        sprite->draw();
    }
}/**/

OpenGLRenderer::OpenGLRenderer() {
    this->resolution = platform_get_window_size();
    this->screenSize = platform_get_screen_size();

    load_gl_functions();
    this->initRenderingParameters();

    this->initializing = false;
}

void OpenGLRenderer::render() {
    if (initializing) return;
    this->refreshRenderingParameters();

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
}



void OpenGLRenderer::renderSkybox() {

}

void OpenGLRenderer::renderWorld() {

}

void OpenGLRenderer::renderPostProcessing() {

}

void OpenGLRenderer::renderUI() {

}
