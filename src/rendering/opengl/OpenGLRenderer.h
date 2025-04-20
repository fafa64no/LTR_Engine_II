//
// Created by sebas on 31/12/2024.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "glm.hpp"



class OpenGLRenderer {
public:
    OpenGLRenderer();
    void render();
private:
    bool initializing{true};
    glm::ivec2 resolution{}, screenSize{};

    void initRenderingParameters();

    void refreshRenderingParameters();

    void preparePostProcessing();
    void renderSkybox();
    void renderWorld();
    void renderPostProcessing();
    void renderUI();
};

#endif //OPENGLRENDERER_H
