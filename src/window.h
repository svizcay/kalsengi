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
            bool                    _okay;


            static void windowResizeCallback (GLFWwindow * context, int width, int height);
            static void framebufferResizeCallback (GLFWwindow * context, int width, int height);
            static void errorCallback (int error, const char * description);

        public:
            Window (uint width, uint height, const char * title, bool fullscreen = false);
            ~Window ();
            void setClearColor (float r, float g, float b);
            void setClearColor (float * rgb);
            void queryOpenGLInfo ();
            bool isFine ();

            GLFWwindow * context;

    };
}
#endif /* WINDOW_H */
