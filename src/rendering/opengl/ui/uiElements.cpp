//
// Created by sebas on 25/01/2025.
//

#include "uiElements.h"

#include <game_cfg.h>
#include <SpriteGroup.h>
#include <SpriteWithFilter.h>

#include "textures.h"
#include "rendering_cfg.h"
#include "RenderEngine.h"
#include "clickables.h"

std::vector<Displayable*> ui_sprites;
SpriteGroup* possible_moves_sprite_group;
SpriteGroup* selection_sprite_group;

void initUIElements() {
  initClickables();
}

void addAdditionalUIElement(Displayable* sprite) {
  ui_sprites.push_back(sprite);
  std::sort(ui_sprites.begin(), ui_sprites.end(), compareRenderOrder);
}

void addAdditionalUIElement(Texture* texture, const glm::vec2 size, SpriteTarget* target) {
  addAdditionalUIElement(reinterpret_cast<Displayable *>(new SpriteWithFilter(texture, size, target)));
}

bool compareRenderOrder(Displayable* a, Displayable* b) {
  return a->getDistanceToCamera() < b->getDistanceToCamera();
}

