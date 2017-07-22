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

    shader.use ();

    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };

    unsigned elements[] = {0, 1, 2, 3, 2, 1};

    GLuint vao;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    GLuint ebo;
    glGenBuffers (1, &ebo);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    GLuint vbo;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer (
            0,                                  // vertex attrib index that we are setting. layout (location = index) in vertex shader
            3,                                  // 3 values
            GL_FLOAT,                           // each value is a float
            GL_FALSE,                           // should opengl normalize the values? if true, unsigned values are mapped to [0, 1] and signed values to [-1, 1]
            3 * sizeof(float),                  // stride, ie: the distance in bytes between the beginning of consecutives values (in this case, each position is 3 floats apart of each other)
            (void *) 0);                        // initial offset within the buffer
    /* about the stride size:
     * if we pack multiple vertex data into a buffer, the stride is equal to the size of the package
     * */
    glEnableVertexAttribArray (0);

    glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // other options: GL_FILL

    while ( !glfwWindowShouldClose (window.context) ) {

        processInput (window.context);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays (GL_TRIANGLES, 0, 3);  // 2nd parameter: starting index. 3rd parameter: how many vertices
        glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
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
