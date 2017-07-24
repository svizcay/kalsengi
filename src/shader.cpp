#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>


using namespace kalsengi;
using namespace std;

GLuint Shader::compileShader (string pathToSrc, GLenum shaderType)
{
    string src      = readFile(pathToSrc);
    GLuint shader   = glCreateShader (shaderType);
    const char * sourceAddress = src.c_str();
    glShaderSource (shader, 1, &sourceAddress, nullptr);
    glCompileShader (shader);

    return shader;
}

GLuint Shader::linkProgram (const vector<GLuint> & shaders)
{
    GLuint program = glCreateProgram ();

    for (auto & shader : shaders) {
        glAttachShader (program, shader);
    }
    glLinkProgram (program);

    return program;
}

Shader::Shader (string pathToVertShader, string pathToFragShader)
{

    // shaderPaths[Type::VERTEX]   = pathToVertShader;
    // shaderPaths[Type::FRAGMENT] = pathToFragShader;

    shaderPaths[GL_VERTEX_SHADER]   = pathToVertShader;
    shaderPaths[GL_FRAGMENT_SHADER] = pathToFragShader;

    GLuint vertexShader    = compileShader (pathToVertShader, GL_VERTEX_SHADER);
    GLuint fragmentShader  = compileShader (pathToFragShader, GL_FRAGMENT_SHADER);


    if (!compileErrors (vertexShader, GL_VERTEX_SHADER)) {
        if (!compileErrors (fragmentShader, GL_FRAGMENT_SHADER)) {
            
            vector<GLuint> shaders;
            shaders.push_back(vertexShader);
            shaders.push_back(fragmentShader);
            GLuint program = linkProgram(shaders);

            if (!linkErrors (program)) {
                _programID = program;
            }
        }
    }

    glDeleteShader (vertexShader);
    glDeleteShader (fragmentShader);
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

void Shader::reload ()
{
    if (_programID != 0) {
        glDeleteProgram (_programID);
        _programID = 0;
    }

    vector<GLuint> shaders;

    for (auto iter = shaderPaths.begin(); iter != shaderPaths.end(); iter++) {
        GLuint shader = compileShader(iter->second, iter->first);
        if (!compileErrors (shader, iter->first)) {
            shaders.push_back(shader);
        }
    }

    GLuint program = linkProgram(shaders);
    if (!linkErrors (program)) {
        _programID = program;
    }
}
