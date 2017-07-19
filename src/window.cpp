#include "window.h"
#include <iostream>

using namespace kalsengi;
using namespace std;


Window::Window (uint width, uint height, const char * title, bool fullscreen) :
    _width(width), _height(height), _title(title)
{
    glfwInit ();
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWmonitor * primaryMonitor = glfwGetPrimaryMonitor ();

    const GLFWvidmode * mode = glfwGetVideoMode (primaryMonitor);

    if (fullscreen) {
        context = glfwCreateWindow (mode->width, mode->height, title, primaryMonitor, nullptr);
    } else {
        context = glfwCreateWindow (width, height, title, nullptr, nullptr);
    }

    if (context == nullptr) {
        cerr << "Failed to create GLFW window" << endl;
    } else {
        glfwMakeContextCurrent (context);
        if (!gladLoadGL ()) {
            cerr << "Failed to initialize glad" << endl;
        }
    }
}

Window::~Window ()
{
    glfwTerminate ();
}


void Window::setClearColor (float r, float g, float b)
{
    glClearColor (r, g, b, 1.0f);
}
