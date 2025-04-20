//
// Created by simon on 21/04/25.
//

#include "TexturedMesh.h"

#include "glFunctions.h"
#include "log.h"
#include "RenderEngine.h"


TexturedMesh::TexturedMesh(Shader* shader, VAO* vao, Texture* texture, Node* parent) {
    this->shader = shader;
    this->vao = vao;
    this->texture = texture;
    if (parent == nullptr)
        ltr_log_error("TexturedMesh: parent is nullptr");
    this->parent = parent;
    this->shader->addDisplayable(this);
}

void TexturedMesh::draw() {
    auto modelTransform = glm::mat4(1.0f);
    if (this->parent != nullptr) {
        modelTransform = this->parent->getTransform();
    }
    this->vao->bind();
    this->texture->bind();
    this->shader->setMat4("model", modelTransform);
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_PER_CUBE);
}

void TexturedMesh::load() {

}

void TexturedMesh::unload() {

}
