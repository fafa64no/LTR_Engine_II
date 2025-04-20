//
// Created by sebas on 29/12/2024.
//

#include "RenderEngine.h"

#include "platform.h"
#include "glRenderer.h"
#include "log.h"

RenderEngine* RenderEngine::instance = nullptr;
glm::ivec2 RenderEngine::windowSize;
glm::ivec2 RenderEngine::maxWindowSize;
float RenderEngine::aspectRatio, RenderEngine::inverseAspectRatio;

RenderEngine::RenderEngine() {
    ltr_log_info("Creating Render Engine");
    if (platform_create_window("Open Your Magic Circuit"))
        exit(EXIT_FAILURE);
    maxWindowSize = platform_get_screen_size();
    ltr_log_error("maxWindowSize ", maxWindowSize.x, " ", maxWindowSize.y);
    updateWindowSize();
    glInit();
}

RenderEngine::~RenderEngine() {
    ltr_log_info("Destroying Render Engine");
}

RenderEngine* RenderEngine::getInstance() {
    if (instance == nullptr) {
        instance = new RenderEngine();
    }
    return instance;
}

void RenderEngine::update(double deltaTime_ms) {
    platform_update_window();
    updateWindowSize();
    glRender();
    platform_swap_buffers();
}

glm::ivec2 RenderEngine::getWindowSize() {
    return windowSize;
}

glm::ivec2 RenderEngine::getMaxWindowSize() {
    return maxWindowSize;
}

float RenderEngine::getWindowAspectRatio() {
    return aspectRatio;
}

float RenderEngine::getWindowInverseAspectRatio() {
    return inverseAspectRatio;
}

void RenderEngine::updateWindowSize() {
    windowSize = platform_get_window_size();
    aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    inverseAspectRatio = static_cast<float>(windowSize.y) / static_cast<float>(windowSize.x);
    ltr_log_info(
        "Window size: ", windowSize.x, " ", windowSize.y,
        "\n\tAspect ratio: ", aspectRatio,
        "\n\tInverse aspect ratio: ", inverseAspectRatio
    );
}