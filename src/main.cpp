#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "engine/shader.hpp"
#include "engine/camera.hpp"
#include "engine/mesh.hpp"
#include "engine/collider.hpp"

#include "player.hpp"
	
double mouse_posX, mouse_posY, last_mouse_posX, last_mouse_posY;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}





int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW hints, version, etc.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	glfwSwapInterval(1);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
	
	glfwGetCursorPos(window, &mouse_posX, &mouse_posX);

    Shader shader("./shaders/default.vert", "./shaders/default.frag");

    std::vector<Vertex> vertices = {
        // Positions            // Normals           // Texture coords
        {{-100.0f, -1.0f, -100.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{-100.0f, -1.0f,  100.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 100.0f, -1.0f,  100.0f},   {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}},
        {{ 100.0f, -1.0f, -100.0f},   {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}}
    };
    std::vector<unsigned int> indices = {0, 1, 2, 2, 0, 3};

    // Create a Mesh object
    Mesh mesh(vertices, indices);
	
	Player player({0.0f, 0.0f, 3.0f}, {0.0f ,0.0f, 0.0f});
	
	float currentFrame = glfwGetTime();
	float lastFrame = currentFrame;
	float deltaTime;
	
    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
		currentFrame = glfwGetTime();
		deltaTime = (currentFrame - lastFrame);
		lastFrame = currentFrame;
        processInput(window);
		
		last_mouse_posX = mouse_posX;
		last_mouse_posY = mouse_posY;
		glfwGetCursorPos(window, &mouse_posX, &mouse_posY);
		
        shader.use();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		player.update(window, shader, deltaTime, (glm::vec2){(float)(mouse_posX - last_mouse_posX), (float)(mouse_posY - last_mouse_posY)});
		
		
        mesh.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();
    return 0;
}