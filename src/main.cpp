#include <iostream>

#include "window.h"
#include "logger.h"
#include "shader.h"


using namespace std;

void processInput (GLFWwindow * window);

int main (int/*argc*/, char* /*argv*/[])
{

    kalsengi::Logger logger ("log.txt");

    int windowWidth = 800;
    int windowHeight = 600;
    const char windowTitle[] = "k a l s e n g i";
    kalsengi::Window window (windowWidth, windowHeight, windowTitle);

    // TODO: update path using cmake path
    kalsengi::Shader shader ("../src/shaders/01.vert.glsl", "../src/shaders/01.frag.glsl");

    while ( !glfwWindowShouldClose (window.context) ) {

        processInput (window.context);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwSwapBuffers (window.context);
        glfwPollEvents ();
    }


    return EXIT_SUCCESS;
}

void processInput (GLFWwindow * window)
{
    if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose (window, true);
    }
}
