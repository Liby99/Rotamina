#ifndef CLOTH_VIEWER_H
#define CLOTH_VIEWER_H

#include "viewer/Viewer.h"
#include "object/cloth/Cloth.h"

namespace rotamina {
    class ClothViewer : public Viewer {
    protected:
        Cloth * cloth;
    public:
        static const int CONTROL_PANEL_WIDTH;
        nanogui::Window * controlPanel;
        ClothViewer(int w, int h, std::string name, Cloth & cloth);
    private:
        void addVar(nanogui::FormHelper * form, std::string name, float & f);
        void addVar(nanogui::FormHelper * form, std::string name, int & i);
    };
}

#endif
