//
// Created by simon on 21/04/25.
//

#ifndef TEXTUREDMESH_H
#define TEXTUREDMESH_H

#include "Displayable.h"
#include "Node.h"

#include "Shader.h"
#include "VAO.h"
#include "Texture.h"

class TexturedMesh : Displayable {
public:
    TexturedMesh(Shader* shader, VAO* vao, Texture* texture, Node* parent);
    void draw() override;
    void load() override;
    void unload() override;
    float getDistanceToCamera() override { return 0; }
protected:
    Shader* shader;
    VAO* vao;
    Texture* texture;
    Node* parent;
};



#endif //TEXTUREDMESH_H
