#ifndef CLOTH_VIEWER_H
#define CLOTH_VIEWER_H

#include "viewer/Viewer.h"
#include "object/cloth/Cloth.h"
#include "physics/Gravity.h"

namespace rotamina {
    class ClothViewer : public Viewer {
    protected:
        Cloth * cloth;
    public:
        static const int CONTROL_PANEL_WIDTH;
        static const int PLAYBACK_PANEL_HEIGHT;
        nanogui::Window * controlPanel;
        ClothViewer(int w, int h, std::string name, Cloth & cloth);
    private:
        void addVar(nanogui::FormHelper * form, std::string name, float & f);
        void addVar(nanogui::FormHelper * form, std::string name, int & i);
    };
}

#endif
