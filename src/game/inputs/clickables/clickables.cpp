//
// Created by sebas on 19/02/2025.
//

#include "clickables.h"

#include <log.h>
#include <RadioButton.h>

std::vector<ClickableArea*> clickable_areas_lmb;
std::vector<ClickableArea*> clickable_areas_rmb;
std::vector<ClickableArea*> clickable_areas_mmb;

RadioButton* radio_button_test;
Button* screen_blocker;

void initClickables() {
    std::sort(clickable_areas_lmb.begin(), clickable_areas_lmb.end(), compareClickOrder);
    std::sort(clickable_areas_rmb.begin(), clickable_areas_rmb.end(), compareClickOrder);
    std::sort(clickable_areas_mmb.begin(), clickable_areas_mmb.end(), compareClickOrder);
}

void addClickableAreaLMB(ClickableArea* clickable_area) {
    clickable_areas_lmb.push_back(clickable_area);
}

void addClickableAreaRMB(ClickableArea* clickable_area) {
    clickable_areas_rmb.push_back(clickable_area);
}

void addClickableAreaMMB(ClickableArea* clickable_area) {
    clickable_areas_mmb.push_back(clickable_area);
}

bool compareClickOrder(const ClickableArea* a, const ClickableArea* b) {
    return a->getDistanceToCamera() > b->getDistanceToCamera();
}
