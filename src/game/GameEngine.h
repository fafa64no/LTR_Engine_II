//
// Created by sebas on 29/12/2024.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <Context.h>

#include "Engine.h"



class GameEngine final : public Engine {
public:
    GameEngine();
    ~GameEngine() override;
    static GameEngine* getInstance();
    void update(double deltaTime_ms) override;
    void clickBoardAtPos(int x, int y);
private:
    inline static GameEngine* instance = nullptr;
    context_type* context = new context_type();
    bool receivedClick = false;
    int lastClickX{-1}, lastClickY{-1};
};



#endif //GAMEENGINE_H
