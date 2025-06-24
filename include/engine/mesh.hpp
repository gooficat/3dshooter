#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "engine/shader.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    // Constructor
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    // Destructor
    ~Mesh();

    // Render the mesh
    void draw(Shader& shader);

    // Model matrix
    glm::mat4 modelMatrix;

private:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // OpenGL data
    GLuint VAO, VBO, EBO;
    
    // Initialize OpenGL buffers and arrays 
    void setupVAO();
};

#endif