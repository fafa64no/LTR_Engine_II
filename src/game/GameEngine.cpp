//
// Created by sebas on 29/12/2024.
//

#include "GameEngine.h"

#include "effect_List.h"
#include "characters_List.h"
#include "pieces_List.h"
#include "piece_loader.h"
#include "keys.h"

#include <iostream>



GameEngine::GameEngine() {
    std::cout << "Creating Game Engine" << std::endl;
    loadEffectList();
    loadCharactersList();
    loadPiecesList();
    context->chessboard = Chessboard::getInstance();
    init_pieces();
    keys_init();
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
    ///TODO do stuff here Daaaaaave
    if (receivedClick) {
        receivedClick = false;
        Pieces* selectedPiece = Chessboard::getInstance()->getGrid()[lastClickX][lastClickY];
        if (selectedPiece != nullptr && selectedPiece->getIsWhite()) {
            cout << "Y a un truc blanc" << endl;
            selectedPiece->isSelected = true;
            if (context->piece != nullptr)
                context->piece->isSelected = false;
            context->piece = selectedPiece;
        }
    }
    keys_update();
}

void GameEngine::clickBoardAtPos(int x, int y) {
    receivedClick = true;
    lastClickX = x;
    lastClickY = y;
}

