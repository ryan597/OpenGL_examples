// Include standard headers
#include <iostream>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
    // EXAMPLE 3  EXAMPLE 3  EXAMPLE 3  EXAMPLE 3  EXAMPLE 3  EXAMPLE 3
    // ************************************************************************

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    const std::string vertexShaderSource = loadShaderSource( "../SimpleTransform.vertexshader");
    const std::string fragmentShaderSource = loadShaderSource("../SingleColor.fragmentshader");
    unsigned int programID = createShaders(vertexShaderSource, fragmentShaderSource);

    // check if shaders could load
    if (programID == (unsigned int)-1)
    {
        glfwTerminate();
        //std::getchar();
        return -1;
    }

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    //glm::mat4 Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3),  // camera is at (4, 3, 3)
        glm::vec3(0, 0, 0),  // looking at the origin
        glm::vec3(0, 1, 0)   // head is up (set to (0, -1, 0) for upside down)
    );

    // model matrix : identity matrix (will be at origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // model view projection
    glm::mat4 MVP = Projection * View * Model;

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

        glUseProgram(programID);

        // send transformation to the bound shader
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)nullptr
        );

        // draw
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
