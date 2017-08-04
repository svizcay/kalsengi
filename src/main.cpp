#include <iostream>
#include <cmath>

#include "window.h"
#include "logger.h"
#include "shader.h"
#include "time.h"
#include "camera.h"
#include "mesh.h"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

// include everything from glm (we can also pick up individual things)
// optional: define GLM_SWIZZLE to enable swizzle operators
// by doing that compilation takes longer and final binary file will increase its size
// glm uses radians by default (glu uses degrees)
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;

// void processInput (GLFWwindow * window);
// void keyboardCallback (GLFWwindow * window, int key, int scancode, int action, int mods);

unsigned long frameCounter = 0;

int main (int/*argc*/, char* /*argv*/[])
{

    kalsengi::Logger logger ("log.txt");

    int windowWidth = 800;
    int windowHeight = 600;
    const char windowTitle[] = "k a l s e n g i";
    kalsengi::Window window (windowWidth, windowHeight, windowTitle);
    window.queryOpenGLInfo ();

    float backgroundColor[] = {0.5f, 0.5f, 0.5f};
    window.setClearColor(backgroundColor);

    // test
    // glfwSetKeyCallback (window.context, keyboardCallback);

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

    // GLint viewLoc = glGetUniformLocation (shader.id (), "view");

    // shader.setUniform (1, 1.0f);
    shader.setUniform ("asdf1", true);
    shader.setUniform ("asdf2", 1);
    shader.setUniform ("asdf3", 1.1f);

    // translate values are in the last row
    // that means values matrices are col-major (the last col is the one with the translations)
    glm::mat4 model = glm::translate ( glm::mat4(1.0f), glm::vec3 (0.25f, 0.25f, 0.0f) ); 
    glm::vec3 point (0.0f);

    // when using glm::translate, rotate, scale, etc, glm left multiply the given matrix by the new matrix that is being created
    // example: glm::mat4 model = glm::rotate ( translationMatrix , angle, direction ) is equivalent to model = translation * rotation;
    // BE REALLY CAREFUL HERE...glm::translate right multiply the given matrix by a translation matrix

    glm::vec3 translatedPoint = model * glm::vec4(point, 1.0f);
    cout << translatedPoint.x << " " << translatedPoint.y << " " << translatedPoint.z << endl;

    shader.setUniform ("model", model);

    kalsengi::Camera camera;

    glm::mat4 cameraView = camera.view();
    shader.setUniform ("view", camera.view());

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)windowWidth / windowHeight, 0.1f, 100.f);
    shader.setUniform ("projection", projection);

    translatedPoint = cameraView * glm::vec4(translatedPoint, 1.0f);
    cout << translatedPoint.x << " " << translatedPoint.y << " " << translatedPoint.z << endl;

    translatedPoint = projection * glm::vec4(translatedPoint, 1.0f);
    cout << translatedPoint.x << " " << translatedPoint.y << " " << translatedPoint.z << endl;


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << cameraView[i][j] << " ";
        }
        cout << endl;
    }

    // ImGui binding setup
    ImGui_ImplGlfwGL3_Init (window.context, true);

    ImGuiIO& io = ImGui::GetIO();

    std::vector<kalsengi::Vertex> triangleVertices;
    std::vector<unsigned> indices;
    std::vector<kalsengi::Texture> textures;

    kalsengi::Vertex vertexA, vertexB, vertexC;
    vertexA.pos = glm::vec3(0.0f, 0.0f, 0.0f);
    vertexB.pos = glm::vec3(1.0f, -1.0f, 0.0f);
    vertexC.pos = glm::vec3(1.0f, 0.0f, 0.0f);
    triangleVertices.push_back(vertexA);
    triangleVertices.push_back(vertexB);
    triangleVertices.push_back(vertexC);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    kalsengi::Mesh mesh (triangleVertices, indices, textures);

    while ( !glfwWindowShouldClose (window.context) ) {

        glfwPollEvents ();

        camera.update ();

        if (camera.isDirty()) {
            // cout << frameCounter << " updating camera!!" << endl;
            shader.setUniform ("view", camera.view());
        }

        if (io.KeysDown[GLFW_KEY_ESCAPE]) {
            cout << frameCounter << " Esc was pressed!!" << endl;
            glfwSetWindowShouldClose (window.context, true);
        }

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

        // processInput (window.context);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray (vao);
        glDrawArrays (GL_TRIANGLES, 0, 3);  // 2nd parameter: starting index. 3rd parameter: how many vertices
        glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // mesh.draw (shader);


        ImGui_ImplGlfwGL3_NewFrame ();

        {
            ImGui::Text ("camera pos: %.2f %.2f %.2f", camera._position.x, camera._position.y, camera._position.z);

            if (ImGui::ColorEdit3("background", backgroundColor)) {
                window.setClearColor(backgroundColor);
            }
        }

        ImGui::Render ();

        glfwSwapBuffers (window.context);

        frameCounter++;
    }

    ImGui_ImplGlfwGL3_Shutdown ();

    return EXIT_SUCCESS;
}

// void keyboardCallback (GLFWwindow * window, int key, int /*scancode*/, int action, int /*mods*/)
// {
//     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//         glfwSetWindowShouldClose (window, true);
//     } else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
//         cout << frameCounter << " A was pressed callback!!" << endl;
//     }
// }

// void processInput (GLFWwindow * window)
// {
//     if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//         glfwSetWindowShouldClose (window, true);
//     }
// 
//     if (glfwGetKey (window, GLFW_KEY_A) == GLFW_PRESS) {
//         cout << frameCounter << " A was pressed" << endl;
//     }
// }
