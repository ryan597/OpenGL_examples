#pragma once
#include <string>

/* \brief Load the source code for a shader

    \param shaderFile path to the shader source code

    \return source code from the shader file as a string
*/
auto loadShaderSource(const std::string& shaderFile) -> std::string;

/* \brief Create, compiles and attaches the shader. Function takes the source code as arg
    so you can define the code in your cpp file or load it from elsewhere using the loadShaderSource function

    \param vertexShaderSource vertex source code as a string reference
    \param fragmentShaderSource fragment source code as a string reference

    \return ID of the compiled and linked shaders
*/
auto createShaders(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) -> unsigned int;

/* \brief Compiles the shader source code, specify if vertex or fragment type

    \param type type of shader, GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
    \param source shader source code as a string

    \return ID of the compiled shader
*/
auto compileShader(unsigned int type, const std::string& source) -> unsigned int;

//auto LoadShaders(const char* vertex_file_path, const char* fragment_file_path) -> GLuint;
