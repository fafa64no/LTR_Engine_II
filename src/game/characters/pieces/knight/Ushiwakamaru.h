//
// Created by david on 31/01/2025.
//

#ifndef USHIWAKAMARU_H
#define USHIWAKAMARU_H

#include <textures.h>
#include <uiElements.h>

#include "Knight.h"


class Ushiwakamaru final : public Knight {
    protected :
        int CNT_StunEffect = 0;
    public:
        Ushiwakamaru(int startX, int startY, bool white, Characters_List hero,
            Pieces_List pieces_root)
            : Knight(startX, startY, white, hero, pieces_root) {
            addAdditionalUIElement(ushiwakamaruTexture, glm::vec2(0.1 * 1080.0/1920.0, 0.1), this);
        }

        [[nodiscard]] vector<Effect_List> getCasterEffects() const override;
        [[nodiscard]] vector<pair<int, int>> getEffectRange(Effect_List effect) const override;
        void passive(void* arg) override;
        bool canEvolve(void* arg) override;
        void evolvedForm(void* arg) override;


};



#endif //USHIWAKAMARU_H
