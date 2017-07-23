#include "window.h"
#include <iostream>

using namespace kalsengi;
using namespace std;


Window::Window (uint width, uint height, const char * title, bool fullscreen) :
    _width(width), _height(height), _title(title), _okay(false)
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
            _okay = true;
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

void Window::queryOpenGLInfo ()
{
    if (_okay) {
        GLenum intParams[] = {
            GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
            GL_MAX_CUBE_MAP_TEXTURE_SIZE,
            GL_MAX_DRAW_BUFFERS,
            GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
            GL_MAX_TEXTURE_IMAGE_UNITS,
            GL_MAX_TEXTURE_SIZE,
            GL_MAX_VARYING_FLOATS,
            GL_MAX_VERTEX_ATTRIBS,
            GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
            GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        };
        
        const char* intParamsLabels[] = {
            "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
            "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
            "GL_MAX_DRAW_BUFFERS",
            "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
            "GL_MAX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_TEXTURE_SIZE",
            "GL_MAX_VARYING_FLOATS",
            "GL_MAX_VERTEX_ATTRIBS",
            "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        };

        for (unsigned i = 0; i < 10; i++) {
            int val = 0;
            glGetIntegerv (intParams[i], &val);
            cout << intParamsLabels[i] << ": " << val << endl;
        }

        int dim[2];
        glGetIntegerv (GL_MAX_VIEWPORT_DIMS, dim);
        cout << "GL_MAX_VIEWPORT_DIMS" << ": " << dim[0] << "x" << dim[1] << endl;

        unsigned char val = 0;
        glGetBooleanv (GL_STEREO, &val);
        cout << "GL_STEREO" << ": " << (unsigned int) val << endl;
        

    } else {
        cerr << "ERROR: OpenGL context could not be initialized." << endl;
    }
}

bool Window::isFine ()
{
    return _okay;
}
