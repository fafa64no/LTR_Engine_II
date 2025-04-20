//
// Created by simon on 20/04/25.
//

#include "Node.h"

#include "quaternion.hpp"


Node::Node() {
    this->position = glm::vec3(0, 0, 0);
    this->scale = glm::vec3(1, 1, 1);
    this->rotation = glm::quat(1, 0, 0, 0);
    this->parent = nullptr;
}

Node::Node(Node* parent)  {
    this->position = glm::vec3(0, 0, 0);
    this->scale = glm::vec3(1, 1, 1);
    this->rotation = glm::quat(1, 0, 0, 0);
    this->parent = parent;
}

Node::Node(const glm::vec3 position)  {
    this->position = position;
    this->scale = glm::vec3(1, 1, 1);
    this->rotation = glm::quat(1, 0, 0, 0);
    this->parent = nullptr;
}

Node::Node(const glm::vec3 position, Node* parent)  {
    this->position = position;
    this->scale = glm::vec3(1, 1, 1);
    this->rotation = glm::quat(1, 0, 0, 0);
    this->parent = parent;
}

Node::Node(const glm::vec3 position, const glm::quat rotation)  {
    this->position = position;
    this->scale = glm::vec3(1, 1, 1);
    this->rotation = rotation;
    this->parent = nullptr;
}

Node::Node(const glm::vec3 position, const glm::quat rotation, Node* parent)  {
    this->position = position;
    this->scale = glm::vec3(1, 1, 1);
    this->rotation = rotation;
    this->parent = parent;
}

Node::Node(const glm::vec3 position, const glm::vec3 scale, const glm::quat rotation)  {
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    this->parent = nullptr;
}


Node::Node(const glm::vec3 position, const glm::vec3 scale, const glm::quat rotation, Node* parent) {
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    this->parent = parent;
}

void Node::registerChild(Node* child) {
    this->children.emplace_back(child);
}

[[nodiscard]] glm::vec3 Node::getPosition() const {
    return position;
}

[[nodiscard]] glm::vec3 Node::getScale() const {
    return scale;
}

[[nodiscard]] glm::quat Node::getRotationQuaternion() const {
    return rotation;
}

glm::mat4 Node::getTransform() const {
    // Compute local transform
    auto localTransform = glm::mat4(1.0f);
    localTransform = glm::translate(localTransform, position);
    localTransform = localTransform * glm::mat4_cast(rotation);
    localTransform = glm::scale(localTransform, scale);
    if (parent != nullptr)
        return parent->getTransform() * localTransform;
    return localTransform;
}

[[nodiscard]] glm::vec3 Node::getWorldPosition() const {
    if (parent == nullptr)
        return position;
    return parent->getPosition() + position;
}