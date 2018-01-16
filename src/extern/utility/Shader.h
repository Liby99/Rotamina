#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <nanogui/glutil.h>

namespace rotamina {
    
    class Shader : public nanogui::GLShader {
        private:
            
            static Shader * defaultShader;
            
        public:
            
            Shader();
            // Shader(std::string filename)
            
            static Shader * getDefaultShader();
            static void finish();
    };
}

#endif
