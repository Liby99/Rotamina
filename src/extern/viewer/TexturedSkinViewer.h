#ifndef TEXTURED_SKIN_VIEWER_H
#define TEXTURED_SKIN_VIEWER_H

#include "viewer/SkinViewer.h"
#include "object/skin/TexturedSkin.h"

namespace rotamina {
    class TexturedSkinViewer : public SkinViewer {
        public:
            TexturedSkinViewer(int, int, std::string, TexturedSkin &);
            static void createViewer(int, int, std::string, TexturedSkin & skin, std::function<void(TexturedSkinViewer &)>);
        protected:
            virtual void showSkeleton();
            virtual void showSkin();
    };
}

#endif
