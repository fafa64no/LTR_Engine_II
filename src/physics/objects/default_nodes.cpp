//
// Created by simon on 20/04/25.
//

#include "default_nodes.h"

Node* world_origin_node;
Node* debug_pos_node;
Node* free_cam_node;

void load_default_nodes() {
    world_origin_node = new Node();

    debug_pos_node = new Node(
        glm::vec3(-1, 0, 0)
    );

    free_cam_node = new Node(
        glm::vec3(0, -1, 0)
    );
}