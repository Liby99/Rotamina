#include "viewer/component/InteractiveScene.h"

using namespace rotamina;

InteractiveScene::InteractiveScene(Widget * parent) : Scene(parent) {
    
}

InteractiveScene::~InteractiveScene() {
    Scene::~Scene();
}

bool InteractiveScene::mouseButtonEvent(const Eigen::Vector2i & p, int button, bool down, int modifiers) {
    return false;
}
