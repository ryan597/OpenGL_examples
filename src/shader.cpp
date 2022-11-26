#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <GL/glew.h>

#include "shader.h"

auto LoadShaders(const char* vertex_file_path, const char* fragment_file_path) -> GLuint
{
    // create shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // read Vertex Shader code
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        std::cout << "Cannot open " << vertex_file_path << '\n';
        return -1;
    }

    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
    else
    {
        std::cout << "Cannot open " << fragment_file_path << '\n';
        return -1;
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // compile vertex shader
    std::cout << "Compiling shader: " << vertex_file_path << '\n';
    const char* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
    glCompileShader(VertexShaderID);
    // check shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        std::cout << &VertexShaderErrorMessage[0] << '\n';
    }

    // compile fragment shader
    std::cout << "Compiling shader: " << fragment_file_path << '\n';
    const char* FragmentShaderPointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentShaderPointer, nullptr);
    glCompileShader(FragmentShaderID);

    // check shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        std::cout << &FragmentShaderErrorMessage[0] << '\n';
    }

    // link program
    std::cout << "Linking program\n";
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // check program
    glGetProgramiv(ProgramID, GL_COMPILE_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
        std::cout << &ProgramErrorMessage[0] << '\n';
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}