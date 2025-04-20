//
// Created by sebas on 06/02/2025.
//

#ifndef SPRITEWITHFILTER_H
#define SPRITEWITHFILTER_H

#include <Sprite.h>


class SpriteWithFilter : Sprite {
public:
    SpriteWithFilter(Texture* texture, glm::vec2 size, SpriteTarget* target) : Sprite(texture, size, target) {
        this->shader = nullptr;
    };
    SpriteWithFilter(Texture* texture, glm::vec2 size, SpriteTarget* target, const float layer) : Sprite(texture, size, target, layer) {
        this->shader = nullptr;
    };
    void draw() override;
};



#endif //SPRITEWITHFILTER_H
