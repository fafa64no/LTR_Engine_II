//
// Created by simon on 23/02/25.
//

#ifndef EFFECT_CONTEXT_H
#define EFFECT_CONTEXT_H

#include <Pieces.h>

struct effect_context_type {
    Pieces* source_piece;
    std::vector<Pieces*> friendly_pieces;
    std::vector<Pieces*> enemy_pieces;
    std::vector<std::pair<int, int>> positions;
    EffectInstance effect_instance;
};

#endif //EFFECT_CONTEXT_H
