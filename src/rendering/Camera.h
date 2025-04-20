//
// Created by simon on 21/04/25.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "Node.h"


class Camera {
public:
    Camera(Node* parent, glm::vec3 camUp, glm::vec3 camFront);
    glm::mat4 getViewMatrix() const;
private:
    Node* parent;
    glm::vec3 camUp{};
    glm::vec3 camFront{};
    glm::mat4 viewMatrix{};
};



#endif //CAMERA_H
