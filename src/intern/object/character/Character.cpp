#include "object/character/Character.h"

using namespace rotamina;

Character::Character() : Object() {
    showSkinFlag = true;
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

Skeleton & Character::getSkeleton() {
    return skeleton;
}

Skin & Character::getSkin() {
    return skin;
}

void Character::update() {
    getSkeleton().update();
    getSkin().update(skeleton.getJointTransforms());
}

void Character::draw(Shader & shader) {
    if (showSkinFlag) {
        getSkin().draw(shader);
    }
    else {
        getSkeleton().draw(shader);
    }
}
