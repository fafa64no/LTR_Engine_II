//
// Created by sebas on 29/12/2024.
//

#include "GameEngine.h"

#include "effect_List.h"
#include "characters_List.h"
#include "pieces_List.h"
#include "piece_loader.h"

#include <iostream>

GameEngine::GameEngine() {
    std::cout << "Creating Game Engine" << std::endl;
    loadEffectList();
    loadCharactersList();
    loadPiecesList();
    context.chessboard = Chessboard::getInstance();
    init_pieces();
}

GameEngine::~GameEngine() {
    std::cout << "Destroying Game Engine" << std::endl;
}

GameEngine* GameEngine::getInstance() {
    if (instance == nullptr) {
        instance = new GameEngine();
    }
    return instance;
}

void GameEngine::update(double deltaTime_ms) {

}