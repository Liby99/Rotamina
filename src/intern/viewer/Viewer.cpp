#include "viewer/Viewer.h"

Viewer * Viewer::app = nullptr;

Viewer::Viewer(int width, int height, std::string name) : nanogui::Screen(Eigen::Vector2i(width, height), name) {
    using namespace nanogui;
    
    shader.init(
        /* An identifying name */
        "a_simple_shader",

        /* Vertex shader */
        "#version 400\n"
        "layout(location=0) in vec3 Position;\n"
        "layout(location=1) in vec3 Normal;\n"
        "out vec3 fragPosition;\n"
        "out vec3 fragNormal;\n"
        "uniform mat4 ModelMtx=mat4(1);\n"
        "uniform mat4 ModelViewProjMtx=mat4(1);\n"
        "void main() {\n"
        "    gl_Position=ModelViewProjMtx * vec4(Position,1);\n"
        "    fragPosition=vec3(ModelMtx * vec4(Position,1));\n"
        "    fragNormal=vec3(ModelMtx * vec4(Normal,0));\n"
        "}",

        /* Fragment shader */
        "#version 400\n"
        "in vec3 fragPosition;\n"
        "in vec3 fragNormal;\n"
        "uniform vec3 AmbientColor=vec3(0.2);\n"
        "uniform vec3 LightDirection=normalize(vec3(1,5,2));\n"
        "uniform vec3 LightColor=vec3(1);\n"
        "uniform vec3 DiffuseColor=vec3(0.5);\n"
        "out vec3 finalColor;\n"
        "void main() {\n"
        "    vec3 irradiance=AmbientColor + LightColor * max(0,dot(LightDirection,fragNormal));\n"
        "    vec3 reflectance=irradiance * DiffuseColor;\n"
        "    finalColor=sqrt(reflectance);\n"
        "}"
    );
    
    MatrixXu indices(3, 2); /* Draw 2 triangles */
    indices.col(0) << 0, 1, 2;
    indices.col(1) << 2, 3, 0;
    
    MatrixXf positions(3, 4);
    positions.col(0) << -1, -1, 0;
    positions.col(1) <<  1, -1, 0;
    positions.col(2) <<  1,  1, 0;
    positions.col(3) << -1,  1, 0;
    
    MatrixXf normals(3, 4);
    normals.col(0) << 0, 0, 1;
    normals.col(1) << 0, 0, 1;
    normals.col(2) << 0, 0, 1;
    normals.col(3) << 0, 0, 1;
    
    shader.bind();
    shader.uploadIndices(indices);
    shader.uploadAttrib("Position", positions);
    shader.uploadAttrib("Normal", normals);
}

Viewer::~Viewer() {
    shader.free();
}

void Viewer::initiateLayout() {
    using namespace nanogui;
    // TODO: Initiate Layout
}

void Viewer::draw(NVGcontext * ctx) {
    Screen::draw(ctx);
}

void Viewer::drawContents() {
    using namespace nanogui;
    
    // int currTime = glfwGetTime();
    
    // Matrix4 view = camera->getViewMatrix(currTime);
    // Matrix4 pers = camera->getPerspectiveMatrix(currTime);
    //
    // Matrix4 vp = view * pers;
    //
    // for (Object * object : objects) {
    //     Matrix4 mvp = object->getModelMatrix() * vp;
    //
    //     shader.setUniform("modelViewProj", mvp);
    //
    //     object->;
    // }
    //
    
    shader.bind();
    
    Matrix4f model;
    model.setIdentity();
    
    Matrix4f mvp;
    mvp.setIdentity();
    mvp.topLeftCorner<3,3>() = Matrix3f(Eigen::AngleAxisf((float) glfwGetTime(),  Vector3f::UnitZ())) * 0.25f;
    
    mvp.row(0) *= (float) mSize.y() / (float) mSize.x();
    
    shader.setUniform("ModelMtx", model);
    shader.setUniform("ModelViewProjMtx", mvp);
    
    shader.drawIndexed(GL_TRIANGLES, 0, 2);
}

void Viewer::initiate(int width, int height, std::string name, std::function<void(Viewer &)> f) {
    try {
        nanogui::init();
        
        if (app) {
            delete app;
            app = nullptr;
        }
        
        app = new Viewer(width, height, name);
        f(*app);
        app->drawAll();
        app->setVisible(true);
        nanogui::mainloop();
        
        nanogui::shutdown();
    }
    catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
    }
}
