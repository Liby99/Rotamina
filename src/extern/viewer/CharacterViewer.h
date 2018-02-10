// #ifndef SKIN_VIEWER_H
// #define SKIN_VIEWER_H
//
// #include "viewer/SkeletonViewer.h"
// #include "object/character/Character.h"
//
// namespace rotamina {
//     class CharacterViewer : public SkeletonViewer {
//         protected:
//             static const int CONTROL_PANEL_HEIGHT = 50;
//             rotamina::Skin * skin;
//             nanogui::Window * skinControlPanel;
//         public:
//             CharacterViewer(int, int, std::string, Skin & skin);
//             static void createViewer(int, int, std::string, Character & character, std::function<void(CharacterViewer &)>);
//         protected:
//             virtual void showSkeleton();
//             virtual void showSkin();
//     };
// }
//
// #endif
