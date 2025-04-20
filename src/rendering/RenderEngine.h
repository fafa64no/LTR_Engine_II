//
// Created by sebas on 29/12/2024.
//

#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "Engine.h"
#include "glm.hpp"
#include "OpenGLRenderer.h"

#define VERTEX_PER_QUAD 6
#define VERTEX_PER_CUBE 36


class RenderEngine final : Engine {
public:
    RenderEngine();
    ~RenderEngine() override;
    static RenderEngine* getInstance();
    void update(double deltaTime_ms) override;

    static glm::ivec2 getWindowSize() { return instance->windowSize; }
    static glm::ivec2 getMaxWindowSize() { return instance->maxWindowSize; }
    static float getWindowAspectRatio() { return instance->aspectRatio; }
    static float getWindowInverseAspectRatio() { return instance->inverseAspectRatio; }
private:
    static RenderEngine* instance;
    OpenGLRenderer* renderer;
    glm::ivec2 windowSize{};
    glm::ivec2 maxWindowSize{};
    // Aspect ratio > 1 in landscape mode
    float aspectRatio{1.0f}, inverseAspectRatio{1.0f};
    void updateWindowSize();
};



#endif //RENDERENGINE_H
