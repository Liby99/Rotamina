#include "viewer/Viewer.h"

void Viewer::initiateLayout() {
    
    using namespace nanogui;
    
    // TODO: Initiate Layout
}

void Viewer::draw(NVGcontext * ctx) {
    Screen::draw(ctx);
}

void Viewer::drawContents() {
    using namespace nanogui;

    /* Draw the window contents using OpenGL */
    mShader.bind();

    Matrix4f mvp;
    mvp.setIdentity();
    mvp.topLeftCorner<3,3>() = Matrix3f(Eigen::AngleAxisf((float) glfwGetTime(),  Vector3f::UnitZ())) * 0.25f;

    mvp.row(0) *= (float) mSize.y() / (float) mSize.x();
    
    mShader.setUniform("modelViewProj", mvp);
    
    mShader.drawIndexed(GL_TRIANGLES, 0, 2);
}

Viewer::Viewer() : nanogui::Screen(Eigen::Vector2i(1440, 960), "CSE 169 Animation Viewer") {
    
    using namespace nanogui;
    
    mShader.init(
        /* An identifying name */
        "a_simple_shader",

        /* Vertex shader */
        "#version 330\n"
        "uniform mat4 modelViewProj;\n"
        "in vec3 position;\n"
        "void main() {\n"
        "    gl_Position = modelViewProj * vec4(position, 1.0);\n"
        "}",

        /* Fragment shader */
        "#version 330\n"
        "out vec4 color;\n"
        "uniform float intensity;\n"
        "void main() {\n"
        "    color = vec4(vec3(intensity), 1.0);\n"
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

    mShader.bind();
    mShader.uploadIndices(indices);
    mShader.uploadAttrib("position", positions);
    mShader.setUniform("intensity", 0.5f);
}

Viewer::~Viewer() {
    mShader.free();
}
