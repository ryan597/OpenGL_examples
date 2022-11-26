#pragma once
#include <string>

auto loadShaderSource(const std::string& shaderFile) -> std::string;
auto createShaders(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) -> unsigned int;
auto compileShader(unsigned int type, const std::string& source) -> unsigned int;

//auto LoadShaders(const char* vertex_file_path, const char* fragment_file_path) -> GLuint;
