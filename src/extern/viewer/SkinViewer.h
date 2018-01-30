#ifndef SKIN_VIEWER_H
#define SKIN_VIEWER_H

#include "viewer/SkeletonViewer.h"
#include "object/skin/Skin.h"

namespace rotamina {
    class SkinViewer : public SkeletonViewer {
        protected:
            rotamina::Skin * skin;
        public:
            SkinViewer(int, int, std::string, Skin & skin);
            static void createViewer(int, int, std::string, Skin & skin, std::function<void(SkinViewer &)>);
    };
}

#endif
