#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>


using namespace kalsengi;
using namespace std;

Shader::Shader (string pathToVertShader, string pathToFragShader)
{
    // read vertex shader
    string vertexShaderSrc = readFile(pathToVertShader);
    GLuint vertexShader = glCreateShader (GL_VERTEX_SHADER);
    const char * sourceAddress = vertexShaderSrc.c_str();
    glShaderSource (vertexShader, 1, &sourceAddress, nullptr);
    glCompileShader (vertexShader);

    if (!compileErrors (vertexShader, GL_VERTEX_SHADER)) {

        string fragmentShaderSrc = readFile(pathToFragShader);
        GLuint fragmentShader = glCreateShader (GL_FRAGMENT_SHADER);
        sourceAddress = fragmentShaderSrc.c_str();
        glShaderSource (fragmentShader, 1, &sourceAddress, nullptr);
        glCompileShader (fragmentShader);

        if (!compileErrors (fragmentShader, GL_FRAGMENT_SHADER)) {
            GLuint program = glCreateProgram ();
            glAttachShader (program, vertexShader);
            glAttachShader (program, fragmentShader);
            glLinkProgram (program);

            if (!linkErrors (program)) {
                _programID = program;

                glDeleteShader (vertexShader);
                glDeleteShader (fragmentShader);
            }
        } else {
            glDeleteShader (vertexShader);
        }
    }
}

std::string Shader::readFile (std::string path)
{
    string content;
    ifstream file (path);
    if (file.is_open()) {

        stringstream strStream;
        strStream << file.rdbuf ();

        file.close();
        
        content = strStream.str();
    } else {
        cerr << "ERROR: unable to open file " << path << "." << endl;
    }

    return content;
}

bool Shader::compileErrors (GLuint shaderID, GLenum shaderType)
{

    GLint success;
    char message[512];
    glGetShaderiv (shaderID, GL_COMPILE_STATUS, &success);

    string shaderTypeStr;
    switch (shaderType)
    {
        case GL_VERTEX_SHADER:
            shaderTypeStr = "vertex shader";
            break;
        case GL_FRAGMENT_SHADER:
            shaderTypeStr = "fragment shader";
            break;
        default:
            shaderTypeStr = "unknown shader";
    }

    if (!success) {
        glGetShaderInfoLog (shaderID, 512, nullptr, message);
        cerr << "ERROR: " << shaderTypeStr << " compilation failed." << endl;
        return true;
    }

    return false;
}

bool Shader::linkErrors (GLuint programID)
{
    GLint success;
    char message[512];
    glGetProgramiv (programID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog (programID, 512, nullptr, message);
        cerr << "ERROR: shader program could not link." << endl;
        return true;
    }

    return false;

}

void Shader::use ()
{
    if (_programID != 0) {
        glUseProgram (_programID);
    } else {
        cerr << "ERROR: trying to use an invalid program." << endl;
    }
}

GLuint Shader::id ()
{
    return _programID;
}
