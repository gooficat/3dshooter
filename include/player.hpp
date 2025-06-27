#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "engine/collider.hpp"
#include "engine/camera.hpp"
#include "engine/shader.hpp"

static float GRAVITY;
static float PLAYER_ACCEL_AIR, PLAYER_JUMP_VELOCITY;
static float CAM_ACCEL, MOUSE_SENS;


class Player {
public:
	SphereCollider* collider;
	PerspectiveCamera* camera;
	glm::vec3 position, rotation, velocity, head, direction;
	float accel;
	glm::vec3 _accel;
	Player(glm::vec3 position, glm::vec3 rotation);
	~Player();
	
	void update(GLFWwindow* window, Shader& shader, float deltaTime, glm::vec2 mouseRelative);
private:
};


#endif