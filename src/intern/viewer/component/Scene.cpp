#include "viewer/component/Scene.h"

using namespace rotamina;

const float Scene::SCROLL_SPEED = 0.1f;
const float Scene::ROTATE_SPEED = 0.004f;
const float Scene::MOVE_SPEED = 0.1f;

Scene::Scene(Widget * parent) : nanogui::GLCanvas(parent),
    azimuth(0), incline(0), dist(3), hasDisplayCallback(false),
    w(false), a(false), s(false), d(false) {
    shader = new Shader();
    shader->init();
}

Scene::~Scene() {
    shader->free();
    delete shader;
}

void Scene::setSize(int width, int height) {
    GLCanvas::setSize({ width, height });
    camera.setSize(width, height);
}

void Scene::setWidth(int width) {
    GLCanvas::setWidth(width);
    camera.setWidth(width);
}

void Scene::setHeight(int height) {
    GLCanvas::setHeight(height);
    camera.setHeight(height);
}

int Scene::getWidth() {
    return camera.getWidth();
}

int Scene::getHeight() {
    return camera.getHeight();
}

void Scene::addObject(rotamina::Object & obj) {
    objects.push_back(&obj);
}

bool Scene::removeObject(int i) {
    if (objects.size() <= i) {
        return false;
    }
    objects.erase(objects.begin() + i);
    return true;
}

unsigned int Scene::objectCount() {
    return objects.size();
}

Camera & Scene::getCamera() {
    return camera;
}

void Scene::updateCamera() {
    using namespace Eigen;
    
    // First rotate the camera
    Vector3f pos = Vector3f(0, 0, dist);
    Matrix3f m;
    m = AngleAxisf(azimuth, Vector3f::UnitY()) * AngleAxisf(incline, Vector3f::UnitX());
    
    // Then move the camera
    Vector3f forw = (camera.getTarget() - camera.getPosition()).normalized(),
             right = forw.cross(camera.getUp()).normalized();
    if (w) camera.setTarget(camera.getTarget() + forw * MOVE_SPEED);
    if (a) camera.setTarget(camera.getTarget() - right * MOVE_SPEED);
    if (s) camera.setTarget(camera.getTarget() - forw * MOVE_SPEED);
    if (d) camera.setTarget(camera.getTarget() + right * MOVE_SPEED);
    
    // Finally set camera position
    camera.setPosition(camera.getTarget() + m * pos);
}

Shader & Scene::getShader() {
    return *shader;
}

void Scene::setShader(Shader & shader) {
    this->shader = &shader;
}

void Scene::setDisplayCallback(std::function<void()> cb) {
    this->hasDisplayCallback = true;
    this->displayCallback = cb;
}

bool Scene::keyboardEvent(int key, int scancode, int action, int modifiers) {
    if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS) {
            w = true;
        }
        else if (action == GLFW_RELEASE) {
            w = false;
        }
    }
    else if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            a = true;
        }
        else if (action == GLFW_RELEASE) {
            a = false;
        }
    }
    else if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS) {
            s = true;
        }
        else if (action == GLFW_RELEASE) {
            s = false;
        }
    }
    else if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            d = true;
        }
        else if (action == GLFW_RELEASE) {
            d = false;
        }
    }
    return true;
}

bool Scene::mouseDragEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) {
    azimuth -= rel[0] * ROTATE_SPEED;
    incline = fmaxf(-M_PI / 2 + 0.01f, fminf(M_PI / 2 - 0.01f, incline - rel[1] * ROTATE_SPEED));
    return true;
}

bool Scene::mouseMotionEvent(const Eigen::Vector2i & p, const Eigen::Vector2i & rel, int button, int modifiers) {
    return true;
}

bool Scene::scrollEvent(const Eigen::Vector2i & p, const Eigen::Vector2f & rel) {
    dist = fmaxf(0.01f, dist - rel[1] * SCROLL_SPEED);
    return true;
}

void Scene::drawGL() {
    glEnable(GL_DEPTH_TEST);
    
    // Update camera related info
    updateCamera();
    shader->bind();
    shader->setUniform("viewPersp", camera.getViewPerspective());
    
    // Draw all the objects
    for (rotamina::Object * obj : objects) {
        obj->update();
        if (!obj->isHidden()) {
            obj->draw(*shader);
        }
    }
    
    // Give Display Callback
    if (hasDisplayCallback) {
        displayCallback();
    }
    
    glDisable(GL_DEPTH_TEST);
}
