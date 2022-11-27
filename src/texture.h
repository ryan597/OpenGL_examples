#pragma once

#include <string>

/* Load BMP image using custom loader */
auto loadBMP(const std::string& imagePath) -> unsigned int;

/* Load DDS file using GLFW's loader */
auto loadDDS(const std::string& imagePath) -> unsigned int;