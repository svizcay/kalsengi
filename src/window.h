#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace kalsengi
{
    class Window {
        protected:
            uint                    _width;
            uint                    _height;
            std::string             _title;

            static void windowResizeCallback (GLFWwindow * context, int width, int height);
            static void framebufferResizeCallback (GLFWwindow * context, int width, int height);

        public:
            Window (uint width, uint height, const char * title, bool fullscreen = false);
            ~Window ();
            void setClearColor (float r, float g, float b);

            GLFWwindow * context;

    };
}
#endif /* WINDOW_H */
