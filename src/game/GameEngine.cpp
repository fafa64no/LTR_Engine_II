//
// Created by sebas on 29/12/2024.
//

#include "GameEngine.h"

#include "keys.h"
#include "log.h"

void game_state_names_Init() {

}

GameEngine::GameEngine() {
    ltr_log_info("Creating Game Engine");

    keys_init();
}

GameEngine::~GameEngine() {
    ltr_log_info("Destroying Game Engine");
}

GameEngine* GameEngine::getInstance() {
    if (instance == nullptr)
        instance = new GameEngine();
    return instance;
}

void GameEngine::update(double deltaTime_ms) {
    keys_update();
}



