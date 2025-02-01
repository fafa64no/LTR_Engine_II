//
// Created by sebas on 24/01/2025.
//

#ifndef TEXTURES_H
#define TEXTURES_H

#include "Texture.h"

enum tex_type {
    TEX_FARID,
    TEX_LTR,
    TEX_FRAME_TEXTURE,
    TEX_BACKGROUND,
    TEX_COUNT
};

extern std::string texNames[TEX_COUNT];

extern Texture* faridTexture;
extern Texture* ltrTexture;
extern Texture* frameTexture;
extern Texture* backgroundTexture;

void loadTextures();
void loadTextureNames();

#endif //TEXTURES_H
