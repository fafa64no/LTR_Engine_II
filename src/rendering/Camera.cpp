//
// Created by simon on 21/04/25.
//

#include "Camera.h"

#include "log.h"


Camera::Camera(Node* parent, const glm::vec3 camUp, const glm::vec3 camFront) {
    if (parent == nullptr)
        ltr_log_error("Camera: parent is nullptr");
    this->parent = parent;
    this->camUp = camUp;
    this->camFront = camFront;
    this->viewMatrix = glm::lookAt(glm::vec3(0, 0, 0), camFront, camUp);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::inverse(parent->getTransform()) * this->viewMatrix;
}
