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

            void            loadShader (std::string pathToSrc, GLenum shaderType);
            void            compile ();
            void            use ();
        protected:
            std::string     readFile (std::string path);
            bool            compileErrors (GLuint shaderID, GLenum shaderType);
            bool            linkErrors (GLuint programID);

            GLuint          _programID;



    };
}

#endif /* SHADER_H */
