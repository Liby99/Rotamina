#ifndef ANIMATION_VIEWER_H
#define ANIMATION_VIEWER_H

#include "viewer/Viewer.h"
#include "object/animator/Animator.h"

namespace rotamina {
    class AnimationViewer : public Viewer {
        protected:
            const static int ANIMATION_CONTROL_HEIGHT;
            Animator * animator;
            nanogui::Window * animationControlWindow;
            nanogui::Button * playPauseBtn;
            nanogui::Button * stopBtn;
            nanogui::Label * timeText;
        public:
            AnimationViewer(int, int, std::string, Animator &);
            virtual void displayCallback();
            static void create(int, int, std::string, Animator &, std::function<void(AnimationViewer &)>);
        protected:
            void togglePlay();
            bool isPlaying();
            void play();
            void pause();
            void stop();
    };
}

#endif
