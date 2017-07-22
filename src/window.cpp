#include "window.h"
#include <iostream>

using namespace kalsengi;
using namespace std;


Window::Window (uint width, uint height, const char * title, bool fullscreen) :
    _width(width), _height(height), _title(title)
{
    cout << "stating GLFW " << glfwGetVersionString () << endl;
    glfwSetErrorCallback (errorCallback);

    glfwInit ();
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWmonitor * primaryMonitor = glfwGetPrimaryMonitor ();

    const GLFWvidmode * mode = glfwGetVideoMode (primaryMonitor);

    if (fullscreen) {
        _width = mode->width;
        _height = mode->height;
        context = glfwCreateWindow (_width, _height, title, primaryMonitor, nullptr);
    } else {
        context = glfwCreateWindow (width, height, title, nullptr, nullptr);
    }

    if (context == nullptr) {
        cerr << "Failed to create GLFW window" << endl;
    } else {
        glfwMakeContextCurrent (context);

        // glfwSetWindowSizeCallback(context, windowResizeCallback);

        // set initial viewport
        glfwSetFramebufferSizeCallback (context, framebufferResizeCallback);

        if (!gladLoadGL ()) {
            cerr << "Failed to initialize glad" << endl;
        } else {
            glViewport (0, 0, _width, _height);
            setClearColor(0.45f, 0.45f, 0.45f);
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

void Window::windowResizeCallback (GLFWwindow * /*context*/, int width, int height)
{
    cout << "new window's size: " << width << "x" << height << endl;
}

void Window::framebufferResizeCallback (GLFWwindow * /*context*/, int width, int height)
{
    // cout << "new framebuffer's size: " << width << "x" << height << endl;
    glViewport(0, 0, width, height);
}

void Window::errorCallback (int error, const char * description)
{
    cerr << "ERROR: code " << error << ". " << description << endl;
}
