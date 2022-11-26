// Include standard headers
#include <iostream>
#include <cstdlib>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "shader.h"

auto main() -> int
{
    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() )
    {
        std::cout << "Failed to initialize GLFW\n";
        std::getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow( 1024, 768, "Example Window", nullptr, nullptr);
    if( window == nullptr ){
        std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n";
        std::getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout <<"Failed to initialize GLEW\n";
        std::getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // ************************************************************************
    // EXAMPLE 2  EXAMPLE 2  EXAMPLE 2  EXAMPLE 2  EXAMPLE 2  EXAMPLE 2
    // ************************************************************************

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // create and compile the GLSL program from the shaders
    std::string vertexShaderSource = loadShaderSource("../SimpleVertexShader.vertexshader");
    std::string fragmentShaderSource = loadShaderSource("../SimpleFragmentShader.fragmentshader");
    unsigned int programID = createShaders(vertexShaderSource, fragmentShaderSource);

    //unsigned int programID = LoadShaders("../SimpleVertexShader.vertexshader", "../SimpleFragmentShader.fragmentshader");

    // check if shaders could load
    if (programID == (unsigned int)-1)
    {
        glfwTerminate();
        //std::getchar();
        return -1;
    }

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    do{
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        // use the shader
        glUseProgram(programID);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)nullptr      // array buffer offset
        );

        // draw triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);  // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // cleanup
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    glfwTerminate();
    return 0;
}
