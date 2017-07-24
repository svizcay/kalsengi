#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <vector>
#include <glad/glad.h>

namespace kalsengi
{

    class Shader
    {
        // enum Type_t
        // {
        //     VERTEX                      = 1 << 0,
        //     FRAGMENT                    = 1 << 1,
        //     // GL_COMPUTE_SHADER           = 1 << 2,
        //     // GL_TEST_CONTROL_SHADER      = 1 << 3,
        //     // GL_TEST_EVALUATION_SHADER   = 1 << 4,
        //     // GL_GEOMETRY_SHADER          = 1 << 5,
        // };
        // typedef enum Type_t Type;

        public:
            Shader ();
            Shader (std::string pathToVertShader,
                    std::string pathToFragShader);

            void            loadShader (std::string pathToSrc, GLenum shaderType);
            void            use ();
            GLuint          id ();
            void            reload ();
        protected:
            std::string     readFile (std::string path);
            bool            compileErrors (GLuint shaderID, GLenum shaderType);
            bool            linkErrors (GLuint programID);
            GLuint          compileShader (std::string pathToSrc, GLenum shaderType);
            GLuint          linkProgram (const std::vector<GLuint> & shaders);
            GLuint          _programID;
            // int             _types;
            std::map<GLenum, std::string>  shaderPaths;



    };
}

#endif /* SHADER_H */
