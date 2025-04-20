//
// Created by sebas on 29/12/2024.
//

#include "PhysicsEngine.h"

#include <log.h>

#include "default_nodes.h"

PhysicsEngine::PhysicsEngine() {
    ltr_log_info("Creating Physics Engine");
    load_default_nodes();
}

PhysicsEngine::~PhysicsEngine() {
    ltr_log_info("Destroying Physics Engine");
}

PhysicsEngine* PhysicsEngine::getInstance() {
    if (instance == nullptr) {
        instance = new PhysicsEngine();
    }
    return instance;
}

void PhysicsEngine::update(double deltaTime_ms) {

}