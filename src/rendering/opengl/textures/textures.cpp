//
// Created by sebas on 24/01/2025.
//

#include "textures.h"

#include "RenderEngine.h"

Texture* faridTexture;
Texture* ltrTexture;
Texture* frameTexture;

void loadTextures() {
    GLuint texture_ids[TEX_COUNT];
    glGenTextures(TEX_COUNT, texture_ids);

    faridTexture = new Texture(texture_ids[TEX_FARID], "farid.png", GL_RGBA);
    ltrTexture = new Texture(texture_ids[TEX_LTR], "LTR.png", GL_RGBA);
    frameTexture = new Texture(texture_ids[TEX_FRAME_TEXTURE], RenderEngine::getMaxWindowSize(), GL_RGB);
}