#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <nanogui/glutil.h>

namespace rotamina {
    class Shader : public nanogui::GLShader {
        public:
            Shader();
            bool init();
            bool initTwoLights();
    };
}

#endif
