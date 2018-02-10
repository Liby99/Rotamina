#include "object/character/Character.h"

using namespace rotamina;

Character::Character() : Object() {
    showSkinFlag = true;
}

Skeleton & Character::getSkeleton() {
    return skeleton;
}

Skin & Character::getSkin() {
    return skin;
}

bool Character::isShowingSkin() {
    return showSkinFlag;
}

void Character::setShowSkin() {
    showSkinFlag = true;
}

void Character::setShowSkeleton() {
    showSkinFlag = false;
}

void Character::update() {
    skeleton.update();
    skin.update(skeleton.getJointTransforms());
}

void Character::drawSkin(Shader & shader) {
    skin.draw(shader);
}

void Character::drawSkeleton(Shader & shader) {
    skeleton.draw(shader);
}

void Character::draw(Shader & shader) {
    if (showSkinFlag) {
        drawSkin(shader);
    }
    else {
        drawSkeleton(shader);
    }
}
