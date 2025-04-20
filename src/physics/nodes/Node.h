//
// Created by simon on 20/04/25.
//

#ifndef NODE_H
#define NODE_H

#include <vector>

#include "glm.hpp"
#include "fwd.hpp"
#include "detail/type_quat.hpp"


class Node {
public:
    Node();
    Node(Node* parent);
    Node(glm::vec3 position);
    Node(glm::vec3 position, Node* parent);
    Node(glm::vec3 position, glm::quat rotation);
    Node(glm::vec3 position, glm::quat rotation, Node* parent);
    Node(glm::vec3 position, glm::vec3 scale, glm::quat rotation);
    Node(glm::vec3 position, glm::vec3 scale, glm::quat rotation, Node* parent);
    void registerChild(Node* child);

    [[nodiscard]] glm::vec3 getPosition() const;
    [[nodiscard]] glm::vec3 getScale() const;
    [[nodiscard]] glm::quat getRotation() const;
    [[nodiscard]] glm::quat getRotationQuaternion() const;

    [[nodiscard]] glm::vec3 getWorldPosition() const;
    [[nodiscard]] glm::mat4 getTransform() const;
private:
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;

    Node* parent;
    std::vector<Node*> children;
};



#endif //NODE_H
