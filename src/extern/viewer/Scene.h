#ifndef SCENE_H
#define SCENE_H

#include <nanogui/nanogui.h>
#include <camera/Camera.h>
#include <object/Object.h>

namespace rotamina {
    class Scene : public nanogui::GLCanvas {
        protected:
            rotamina::Shader shader;
            rotamina::Camera camera;
            std::vector<rotamina::Object *> objects;
        public:
            Scene(Widget *);
            ~Scene();
            void addObject(rotamina::Object & obj);
            rotamina::Camera & getCamera();
            virtual void drawGL() override;
    };
}

#endif
