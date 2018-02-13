#ifndef SCENE_H
#define SCENE_H

#include <functional>
#include <nanogui/nanogui.h>
#include <viewer/Camera.h>
#include <object/Object.h>

namespace rotamina {
    class Scene : public nanogui::GLCanvas {
        protected:
            
            static const float SCROLL_SPEED, MOVE_SPEED;
            float azimuth, incline, dist;
            
            const std::function<void()> * displayCallback;
            
            rotamina::Shader * shader;
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
            
            // Object, Camera and Shader
            void addObject(rotamina::Object &);
            bool removeObject(int i);
            unsigned int objectCount();
            rotamina::Camera & getCamera();
            void updateCamera();
            rotamina::Shader & getShader();
            void setShader(rotamina::Shader &);
            
            // Callback
            void setDisplayCallback(std::function<void()> &);
            
            // Control
            virtual bool keyboardEvent(int key, int scancode, int action, int modifiers) override;
            virtual bool mouseDragEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) override;
            virtual bool mouseMotionEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) override;
            virtual bool scrollEvent(const Eigen::Vector2i & p, const Eigen::Vector2f & rel) override;
            virtual void drawGL() override;
    };
}

#endif
