#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "stb_image.h"

#include "engine/shader.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
	int width, height, nrChannels;
	unsigned int id;
	Texture(const char* texturePath);
	void use(Shader& shader);
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();
    virtual void draw(Shader& shader);

    glm::mat4 modelMatrix;

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    GLuint VAO, VBO, EBO;
    
protected:
    void setupVAO();
};

class TextureMesh : public Mesh {
public:
	Texture* texture;
	TextureMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture* texture);
	void draw(Shader& shader) override;
private:
	
};

#endif