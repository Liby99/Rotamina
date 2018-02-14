#include "object/animator/CharacterAnimator.h"

using namespace rotamina;

CharacterAnimator::CharacterAnimator(Animation & a, Character & c) : Animator(a), character(&c) {
    initiateDOFs();
}

Character & CharacterAnimator::getCharacter() {
    return *character;
}

void CharacterAnimator::updateAnimation(float t) {

    // First update skeleton position
    Skeleton & skel = character->getSkeleton();
    skel.transform.setPositionX(animation->getChannel(0).evaluate(t));
    skel.transform.setPositionY(animation->getChannel(1).evaluate(t));
    skel.transform.setPositionZ(animation->getChannel(2).evaluate(t));

    // Then update all the dof
    for (int i = 3; i < animation->getChannelAmount(); i++) {
        Channel & channel = animation->getChannel(i);
        cachedDOFs[i - 3]->setValue(channel.evaluate(t));
    }

    // Finally update the character
    character->update();
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
