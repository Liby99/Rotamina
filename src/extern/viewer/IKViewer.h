#ifndef IK_VIEWER_H
#define IK_VIEWER_H

#include "viewer/SkeletonViewer.h"
#include "object/Cube.h"
#include "object/skeleton/IKSkeleton.h"

namespace rotamina {
    class IKViewer : public SkeletonViewer {
    public:
        
        static const int TARGET_CONTROL_HEIGHT;
        nanogui::Window * targetControlWindow;
        std::vector<Cube *> targetIndicators;

        IKViewer(int, int, std::string, IKSkeleton & skel);
        ~IKViewer();
        static void createViewer(int, int, std::string, IKSkeleton & skel);
        
    private:
        void addTarget();
    };
}

#endif
