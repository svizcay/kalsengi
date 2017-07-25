#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
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

            // set unifoms values
            // void            setBool (std::string key, bool value);
            // void            setInt (std::string key, int value);
            // void            setFloat (std::string key, float value);
            template <typename T>
            void            setUniform (std::string key, T value);


        protected:
            std::string     readFile (std::string path);
            bool            compileErrors (GLuint shaderID, GLenum shaderType);
            bool            linkErrors (GLuint programID);
            GLuint          compileShader (std::string pathToSrc, GLenum shaderType);
            GLuint          linkProgram (const std::vector<GLuint> & shaders);
            GLuint          _programID;
            // int             _types;
            std::map<GLenum, std::string>   shaderPaths;
            std::map<std::string, GLint>    uniformLocations;


            void            setUniform (GLint loc, bool value);
            void            setUniform (GLint loc, int value);
            void            setUniform (GLint loc, float value);

    };

    template<typename T>
    void Shader::setUniform(std::string key, T value)
    {
        auto iter = uniformLocations.find(key);
        if (iter != uniformLocations.end()) {
            // uniform location is known
            if (iter->second != -1) {
                // glUniform1i (iter->second, static_cast<int> (value));
                setUniform(iter->second, value);
            } else {
                std::cerr << "uniform name '" << key << "' was not found in current shader." << std::endl;
            }

        } else {
            // first time setting this uniform. get its location
            GLint location = glGetUniformLocation (_programID, key.c_str());
            if (location == -1) {
                std::cerr << "uniform name '" << key << "' was not found in current shader." << std::endl;
            } else {
                // glUniform1i (location, static_cast<int> (value));
                setUniform(location, value);
            }
            uniformLocations[key] = location;
        }
    }
}

#endif /* SHADER_H */
