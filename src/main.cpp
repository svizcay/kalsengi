#include <iostream>
#include <memory>
#include <functional>

#include "window.h"
#include "logger.h"


using namespace std;

void framebufferSizeCallback (GLFWwindow * window, int width, int height);
void processInput (GLFWwindow * window);

class Node
{
    public:
        int                 _value;
        shared_ptr<Node>    _next;

        Node (int value) : _value(value) {}
        void pushValue (int value)
        {
            if (_next)
                _next->pushValue(value);
            else
                _next.reset (new Node(value));
        }


};


int main (int/*argc*/, char* /*argv*/[])
{

    kalsengi::Logger logger ("log.txt");

    shared_ptr<Node> sp;
    {
        Node root (10);
        root.pushValue (20);
        root.pushValue (30);
        sp = root._next;         // sp points to node with value 20
    }

    cout << "data: " << sp->_value << " " << sp->_next->_value << endl;

    char a1 = 'a';
    char & charRef = std::ref(a1);
    char * charPtr = nullptr;

    cout << "a1 address: " << (void *)&a1 << endl;

    {
        char a2 = 'b';
        charRef = std::ref(a2);       // charRef is not referencing a2!!! charRef is getting a new value, ie: it's equal to a1 = a2;
        charPtr = &a2;

        cout << "a1: " << a1 << endl;
        cout << "a2: " << a2 << endl;
        cout << "change reference value to z" << endl;
        charRef = 'z';
        cout << "a1: " << a1 << endl;
        cout << "a2: " << a2 << endl;

        cout << "a2 address: " << (void *)&(a2) << endl;
        cout << "charRef address: " << (void *)&(charRef) << endl;
    }

    cout << "[after a2 end of scope] charRef address: " << (void *)&charRef << endl;
    cout << "[after a2 end of scope] charPtr address: " << (void *)charPtr << endl;

    cout << "char ref after a2 was destroyed: " << charRef << endl;
    cout << "char pointer after a2 was destroyed: " << *charPtr << endl;

    charRef = 'c';
    cout << "trying to change the reference value to c. new reference value: " << charRef << endl;
    cout << "new pointer value: " << *charPtr << endl;

    *charPtr = 'd';
    cout << "trying to change the pointer value to d. new reference value: " << charRef << endl;
    cout << "new pointer value: " << *charPtr << endl;

    cout << "size of the reference: " << sizeof(charRef) << endl;
    cout << "size of a char: " << sizeof(a1) << endl;

    cout << "value of a1 (the original variable that charRef referenced): " << a1 << endl;


    int windowWidth = 800;
    int windowHeight = 600;
    const char windowTitle[] = "k a l s e n g i";

    kalsengi::Window window (windowWidth, windowHeight, windowTitle, true);

    glViewport (0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback (window.context, framebufferSizeCallback);

    window.setClearColor(0.45f, 0.45f, 0.45f);

    while ( !glfwWindowShouldClose (window.context) ) {

        processInput (window.context);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwSwapBuffers (window.context);
        glfwPollEvents ();
    }


    return EXIT_SUCCESS;
}

void framebufferSizeCallback (GLFWwindow * window, int width, int height)
{
    cout << "changing window's size to " << window << "x" << height << endl;
    glViewport(0, 0, width, height);
}

void processInput (GLFWwindow * window)
{
    if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose (window, true);
    }
}
