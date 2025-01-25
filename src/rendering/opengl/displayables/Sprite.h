//
// Created by sebas on 24/01/2025.
//

#ifndef SPRITE_H
#define SPRITE_H

#include <Texture.h>
#include <VAO.h>
#include <Shader.h>

#include "Displayable.h"

class Sprite : Displayable {
public:
    Sprite(Texture* texture, glm::vec2 position, glm::vec2 size);
    void draw() override;
    void load() override;
    void unload() override;
protected:
    VAO* vao;
    Texture* texture;
    Shader* shader;
    glm::vec2 position{}, size{};
};



#endif //SPRITE_H
