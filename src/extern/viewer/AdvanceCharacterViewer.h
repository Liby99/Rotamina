#ifndef ADVANCE_CHARACTER_VIEWER_H
#define ADVANCE_CHARACTER_VIEWER_H

#include "viewer/CharacterViewer.h"
#include "object/character/AdvanceCharacter.h"

namespace rotamina {
    class AdvanceCharacterViewer : public CharacterViewer {
        protected:
            const static int MORPH_CONTROL_HEIGHT;
            AdvanceCharacter * advanceCharacter;
            rotamina::Shader * origShader;
            rotamina::Shader * textureShader;
            nanogui::Window * morphControlWindow;
        public:
            AdvanceCharacterViewer(int, int, std::string, AdvanceCharacter &);
            ~AdvanceCharacterViewer();
            static void create(int, int, std::string, AdvanceCharacter &, std::function<void(AdvanceCharacterViewer &)>);
        protected:
            virtual void showSkeleton();
            virtual void showSkin();
            virtual void showSkinWithoutTexture();
    };
}

#endif
