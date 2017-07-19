#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

namespace kalsengi
{
    class Shader
    {
        public:
            Shader ();
            Shader (std::string pathToVertShader,
                    std::string pathToFragShader);

            void loadShader (std::string pathToSrc, GLenum shaderType);

            void compile ();
        private:

    };
}

#endif /* SHADER_H */
