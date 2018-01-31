#ifndef SKIN_VIEWER_H
#define SKIN_VIEWER_H

#include "viewer/SkeletonViewer.h"
#include "object/skin/Skin.h"

namespace rotamina {
    class SkinViewer : public SkeletonViewer {
        protected:
            static const int CONTROL_PANEL_HEIGHT = 50;
            rotamina::Skin * skin;
            nanogui::Window * skinControlPanel;
        public:
            SkinViewer(int, int, std::string, Skin & skin);
            static void createViewer(int, int, std::string, Skin & skin, std::function<void(SkinViewer &)>);
        protected:
            virtual void showSkeleton();
            virtual void showSkin();
    };
}

#endif
