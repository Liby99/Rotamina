#ifndef SKELETON_VIEWER_H
#define SKELETON_VIEWER_H

#include <nanogui/nanogui.h>

#include "object/skeleton/Skeleton.h"

#include "Viewer.h"

namespace rotamina {

    class SkeletonViewer : public Viewer {
        protected:
            
            rotamina::Skeleton * skel;
            
            SkeletonViewer(int width, int height, std::string name, Skeleton & skel);
            
            virtual void draw(NVGcontext * ctx);
            virtual void drawContents();
            
        public:
            
            static void createViewer(int width, int height, std::string name, Skeleton & skel, std::function<void(Viewer &)> f);
    };
}

#endif
