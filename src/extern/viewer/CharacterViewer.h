#ifndef CHARACTER_VIEWER_H
#define CHARACTER_VIEWER_H

#include "viewer/SkeletonViewer.h"
#include "object/character/Character.h"

namespace rotamina {
    class CharacterViewer : public SkeletonViewer {
    protected:
        static const int CONTROL_PANEL_HEIGHT = 50;
        Character * character;
        nanogui::Window * skinControlPanel;
    public:
        CharacterViewer(int, int, std::string, Character & skin);
        static void create(int, int, std::string, Character & character, std::function<void(CharacterViewer &)>);
    protected:
        virtual void showSkeleton();
        virtual void showSkin();
    };
}

#endif
