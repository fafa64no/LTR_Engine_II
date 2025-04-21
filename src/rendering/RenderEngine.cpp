//
// Created by sebas on 29/12/2024.
//

#include "RenderEngine.h"

#include "platform.h"
#include "OpenGLRenderer.h"
#include "log.h"

RenderEngine* RenderEngine::instance = nullptr;

RenderEngine::RenderEngine() {
    ltr_log_info("Creating Render Engine");
    if (platform_create_window("Open Your Magic Circuit"))
        exit(EXIT_FAILURE);
    maxWindowSize = platform_get_screen_size();
    ltr_log_info(CONSOLE_COLOR_LIGHT_YELLOW, "Max window size : ", maxWindowSize.x, " ", maxWindowSize.y);
    updateWindowSize();
    ltr_log_debug("AGNEUGNEU");
    renderer = new OpenGLRenderer();
    ltr_log_debug("MA MAMAN DDIT CHUI GENTIL");
}

RenderEngine::~RenderEngine() {
    ltr_log_info("Destroying Render Engine");
}

RenderEngine* RenderEngine::getInstance() {
    if (instance == nullptr)
        instance = new RenderEngine();
    return instance;
}

void RenderEngine::update(double deltaTime_ms) {
    platform_update_window();
    updateWindowSize();
    renderer->render();
    platform_swap_buffers();
}

void RenderEngine::updateWindowSize() {
    windowSize = platform_get_window_size();
    aspectRatio         = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    inverseAspectRatio  = static_cast<float>(windowSize.y) / static_cast<float>(windowSize.x);
}