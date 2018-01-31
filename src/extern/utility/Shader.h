#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <nanogui/glutil.h>

#include "utility/Texture.h"

namespace rotamina {
    class Shader : public nanogui::GLShader {
        public:
            Shader();
            GLuint getProgramId();
            bool init();
            bool initTwoLights();
            bool initTwoLightsTexture();
            void setTexture(const std::string &, const Texture &);
    };
}

#endif
