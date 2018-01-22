#ifndef SKELETON_VIEWER_H
#define SKELETON_VIEWER_H

#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/label.h>
#include <nanogui/checkbox.h>
#include <nanogui/button.h>
#include <nanogui/toolbutton.h>
#include <nanogui/popupbutton.h>
#include <nanogui/combobox.h>
#include <nanogui/progressbar.h>
#include <nanogui/entypo.h>
#include <nanogui/messagedialog.h>
#include <nanogui/textbox.h>
#include <nanogui/slider.h>
#include <nanogui/imagepanel.h>
#include <nanogui/imageview.h>
#include <nanogui/vscrollpanel.h>
#include <nanogui/colorwheel.h>
#include <nanogui/colorpicker.h>
#include <nanogui/graph.h>
#include <nanogui/tabwidget.h>

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
