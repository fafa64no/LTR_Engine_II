//
// Created by sebas on 25/01/2025.
//

#ifndef UIELEMENTS_H
#define UIELEMENTS_H

#include "Sprite.h"
#include "rendering_cfg.h"

#include <vector>

enum ui_sprite_type {
    UI_SPRITE_BACKGROUND,
    UI_SPRITE_BOARD,
    UI_SPRITE_COUNT
};

extern Sprite** ui_sprites;
extern std::vector<Sprite*> ui_additional_sprites;

void initUIElements();
void addAdditionalUIElements(Sprite* sprite);

#endif //UIELEMENTS_H
