#ifndef CHARACTER_ANIMATION_VIEWER
#define CHARACTER_ANIMATION_VIEWER

#include "object/animator/CharacterAnimator.h"
#include "viewer/component/ChannelEditor.h"
#include "viewer/AnimationViewer.h"

namespace rotamina {
    class CharAnimViewer : public AnimationViewer {
        protected:
            const static int SKELETON_VIEWER_WIDTH;
            const static int JOINT_VIEWER_WIDTH;
            const static int CHANNEL_EDITOR_HEIGHT;
            CharacterAnimator * characterAnimator;
            nanogui::Window * skeletonViewer;
            nanogui::Window * channelEditor;
            nanogui::Window * jointViewer;
            std::vector<nanogui::Button *> jointButtonGroup;
            std::vector<nanogui::Button *> dofButtonGroup;
        public:
            CharAnimViewer(int, int, std::string, CharacterAnimator &);
            void push(nanogui::Button *);
            void showChannel(Channel *);
            void showJoint(Joint *);
    };
}

#endif
