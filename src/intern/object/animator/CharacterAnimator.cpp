#include "object/animator/CharacterAnimator.h"

using namespace rotamina;

CharacterAnimator::CharacterAnimator(Animation & a, Character & c) : Animator(a), character(&c) {
    initiateDOFs();
}

void CharacterAnimator::updateAnimation(float t) {
    for (int i = 0; i < animation->getChannelAmount(); i++) {
        Channel & channel = animation->getChannel(i);
        cachedDOFs[i]->setValue(channel.evaluate(t));
    }
}

void CharacterAnimator::draw(Shader & shader) {
    character->draw(shader);
}

void CharacterAnimator::initiateDOFs() {
    Skeleton & skel = character->getSkeleton();
    for (int i = 0; i < skel.jointAmount(); i++) {
        Joint & joint = skel.getJoint(i);
        auto dofs = joint.getDOFs();
        for (int j = 0; j < dofs.size(); j++) {
            cachedDOFs.push_back(dofs[j].second);
        }
    }
}
