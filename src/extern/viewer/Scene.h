#ifndef SCENE_H
#define SCENE_H

#include <nanogui/nanogui.h>
#include <viewer/Camera.h>
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
            void setSize(int, int);
            void setWidth(int);
            void setHeight(int);
            int getWidth();
            int getHeight();
            void addObject(rotamina::Object &);
            rotamina::Camera & getCamera();
            virtual void drawGL() override;
    };
}

#endif
