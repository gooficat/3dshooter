#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/file.hpp"

class Shader {
public:
    // Constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // Use the shader program
    void use();
    // Set uniform integers
    void setInt(const std::string& name, int value);
    // Set uniform floats
    void setFloat(const std::string& name, float value);
    // Set uniform 2D vectors
    void setVec2(const std::string& name, const glm::vec2& value);
    // Set uniform 3D vectors
    void setVec3(const std::string& name, const glm::vec3& value);
    // Set uniform 4D vectors
    void setVec4(const std::string& name, const glm::vec4& value);
    // Set uniform 2x2 matrices
    void setMat2(const std::string& name, const glm::mat2& mat);
    // Set uniform 3x3 matrices
    void setMat3(const std::string& name, const glm::mat3& mat);
    // Set uniform 4x4 matrices
    void setMat4(const std::string& name, const glm::mat4& mat);
private:
    GLuint program;
    // Utility function to load and compile shaders
    GLuint compileShader(GLenum shaderType, const std::string& shaderSource);
};

#endif
