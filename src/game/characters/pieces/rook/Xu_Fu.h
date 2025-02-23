//
// Created by Megaport on 20/02/2025.
//

#ifndef XU_FU_H
#define XU_FU_H


#include <Rook.h>
#include <textures.h>
#include <uiElements.h>
#include "RenderEngine.h"
#include "rendering_cfg.h"



class Xu_Fu final : public Rook{
    protected :
    int CNT_Shield = 0;
    int ShieldChance = 100;
public:
    Xu_Fu(int startX, int startY, bool white, Characters_List hero,
        Pieces_List pieces_root)
        : Rook(startX, startY, white, hero, pieces_root) {
        addAdditionalUIElement(
            xufuTexture,
            glm::vec2(PIECE_SIZE * RenderEngine::getWindowInverseAspectRatio(), PIECE_SIZE),
            this
        );
    }


    //[[nodiscard]] vector<Effect_List> getCasterEffects() const override;
    [[nodiscard]] vector<pair<int, int>> getEffectRange(Effect_List effect) const override;
    bool passive(void* arg) override;
    bool canEvolve(void* arg) override;
    bool evolvedForm(void* arg) override;
    bool SpellActivationCheck(void *arg) override;
    void setPieceGameMode(int piece_game_mode) override;

};



#endif //XU_FU_H
