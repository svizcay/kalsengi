#include <iostream>
#include <cmath>

#include "window.h"
#include "logger.h"
#include "shader.h"
#include "time.h"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"


using namespace std;

void processInput (GLFWwindow * window);

int main (int/*argc*/, char* /*argv*/[])
{

    kalsengi::Logger logger ("log.txt");

    int windowWidth = 800;
    int windowHeight = 600;
    const char windowTitle[] = "k a l s e n g i";
    kalsengi::Window window (windowWidth, windowHeight, windowTitle);
    window.queryOpenGLInfo ();

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

    // glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // other options: GL_FILL
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // other options: GL_FILL

    GLint colorLoc = glGetUniformLocation (shader.id (), "color");

    // shader.setUniform (1, 1.0f);
    shader.setUniform ("asdf1", true);
    shader.setUniform ("asdf2", 1);
    shader.setUniform ("asdf3", 1.1f);

    // ImGui binding setup
    ImGui_ImplGlfwGL3_Init (window.context, true);

    while ( !glfwWindowShouldClose (window.context) ) {

        // temporal. check if we need to reload shaders
        // TODO: check what happens now with uniform locations and thing like that
        if (glfwGetKey (window.context, GLFW_KEY_F5) == GLFW_PRESS) {
            cout << "reloading shaders" << endl;
            shader.reload ();
            shader.use ();
        }

        kalsengi::Time::update ();

        float greenValue = sin (kalsengi::Time::getAbsTime ()) / 2.0f + 0.5f;

        glUniform4f (colorLoc, 0.0f, greenValue, 0.0f, 1.0f);

        processInput (window.context);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays (GL_TRIANGLES, 0, 3);  // 2nd parameter: starting index. 3rd parameter: how many vertices
        glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        ImGui_ImplGlfwGL3_NewFrame ();

        {
            ImGui::Text ("hello world");
        }

        ImGui::Render ();

        glfwSwapBuffers (window.context);
        glfwPollEvents ();
    }

    ImGui_ImplGlfwGL3_Shutdown ();

    return EXIT_SUCCESS;
}

void processInput (GLFWwindow * window)
{
    if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose (window, true);
    }
}
