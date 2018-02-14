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
            nanogui::Window * channelEditorWindow;
            nanogui::Window * jointViewer;
            ChannelEditor * editor;
            Joint * currJoint;
            std::vector<nanogui::Button *> jointButtonGroup;
            std::vector<nanogui::Button *> dofButtonGroup;
        public:
            CharAnimViewer(int, int, std::string, CharacterAnimator &);
            virtual void displayCallback();
            void push(nanogui::Button *);
            void showChannel(Channel *);
            void clearJointInfo();
            void showJoint(Joint *);
    };
}

#endif
