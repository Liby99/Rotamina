#ifndef SKELETON_VIEWER_H
#define SKELETON_VIEWER_H

#include "Viewer.h"
#include "object/skeleton/Skeleton.h"

namespace rotamina {
    class SkeletonViewer : public Viewer {
        protected:
            int JOINTS_VIEWER_WIDTH = 280;
            int JOINT_INFO_VIEWER_WIDTH = 280;
            rotamina::Skeleton * skeleton;
            nanogui::Window * jointsViewer;
            nanogui::Window * jointInfoViewer;
        public:
            SkeletonViewer(int, int, std::string, Skeleton & skel);
            static void createViewer(int, int, std::string, Skeleton & skel, std::function<void(SkeletonViewer &)>);
    };
}

#endif
