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

void Character::draw(Shader & shader) {
    if (showSkinFlag) {
        skin.draw(shader);
    }
    else {
        skeleton.draw(shader);
    }
}
