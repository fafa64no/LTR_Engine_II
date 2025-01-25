//
// Created by sebas on 24/01/2025.
//

#include "Sprite.h"

#include <ext/matrix_transform.hpp>

#include "vaos.h"
#include "shaders.h"
#include "glFunctions.h"
#include "RenderEngine.h"


Sprite::Sprite(Texture* texture, const glm::vec2 position, const glm::vec2 size) {
    this->vao = quadVAO;
    this->texture = texture;
    this->shader = basicSpriteShader;
    this->position = position;
    this->size = size;
}

void Sprite::draw() {
    this->vao->bind();
    this->texture->bind();
    this->shader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = translate(model, glm::vec3(this->position.x,this->position.y,-1));
    model = scale(model, glm::vec3(this->size.x, this->size.y, 1));
    this->shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_PER_QUAD);
}

void Sprite::load() {

}

void Sprite::unload() {

}