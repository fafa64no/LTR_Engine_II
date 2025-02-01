//
// Created by sebas on 25/01/2025.
//

#include "uiElements.h"
#include "textures.h"

Sprite* test;

void initUIElements() {
  test = new Sprite(
    ltrTexture,
    glm::vec2(0.5, 0.5),
    glm::vec2(0.7, 0.7)
  );
}