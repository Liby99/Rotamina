#ifndef INTERACTIVE_SCENE_H
#define INTERACTIVE_SCENE_H

#include "viewer/component/Scene.h"

namespace rotamina {
    class InteractiveScene : public Scene {
    protected:
        Shader * selectionShader;
        
    public:
        InteractiveScene(Widget *);
        ~InteractiveScene();
        virtual bool mouseButtonEvent(const Eigen::Vector2i & p, int button, bool down, int modifiers);
    };
}

#endif
