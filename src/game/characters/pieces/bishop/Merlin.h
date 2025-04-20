//
// Created by Megaport on 19/02/2025.
//

#ifndef MERLIN_H
#define MERLIN_H

#include <Pieces.h>
#include <RenderEngine.h>
#include <rendering_cfg.h>
#include <textures.h>
#include <uiElements.h>


class Merlin final : public Bishop {
    protected :
        bool chooseSpell{false}, passiveUsed{false};
        bool MerlinPowerON{false};
public:
    Merlin(const int startX, const int startY, const bool white, const Characters_List hero)
            : Bishop(startX, startY, white, hero) {
        defaultEffectsRanges[IMMUNITY_AOE] = [this](){return this->getEffectRange(IMMUNITY_AOE);};
        defaultEffectsRanges[IMMUNITY_EFFECT] = [this](){return this->getEffectRange(IMMUNITY_EFFECT);};
        addAdditionalUIElement(
            merlinTexture,
            glm::vec2(PIECE_SIZE * RenderEngine::getWindowInverseAspectRatio(), PIECE_SIZE),
            this
        );
    }

    [[nodiscard]] board_pattern *getEffectRange(Effect_List effect) override;
    bool passive() override;
    bool canEvolve() override;
    bool evolvedForm() override;
    bool SpellActivationCheck() override;
};



#endif //MERLIN_H
