#ifndef ANIMATION_VIEWER_H
#define ANIMATION_VIEWER_H

#include "viewer/Viewer.h"
#include "object/animator/Animator.h"

namespace rotamina {
    class AnimationViewer : public Viewer {
        protected:
            Animator * animator;
            nanogui::Window * animationControlWindow;
        public:
            AnimationViewer(int, int, std::string, Animator &);
            static void create(int, int, std::string, Animator &, std::function<void(AnimationViewer &)>);
        protected:
            // void play();
            // void pause();
            // void stop();
    };
}

#endif
