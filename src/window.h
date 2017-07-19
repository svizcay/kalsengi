#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace kalsengi
{
    class Window {
        private:
            uint                    _width;
            uint                    _height;
            std::string             _title;

        public:
            Window (uint width, uint height, const char * title, bool fullscreen = false);
            ~Window ();
            void setClearColor (float r, float g, float b);

            GLFWwindow * context;

    };
}
#endif /* WINDOW_H */
