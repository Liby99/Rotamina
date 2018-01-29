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
            
            // Setter and Getters
            void setSize(int, int);
            void setWidth(int);
            void setHeight(int);
            int getWidth();
            int getHeight();
            
            // Object and Camera
            void addObject(rotamina::Object &);
            rotamina::Camera & getCamera();
            
            virtual bool mouseMotionEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) override;
            virtual bool scrollEvent(const Eigen::Vector2i & p, const Eigen::Vector2f &rel) override;
            virtual void drawGL() override;
    };
}

#endif
