#include "player.hpp"

float PLAYER_ACCEL_DEFAULT = 13.0f;
float PLAYER_SPEED = 7.0f;

Player::Player(glm::vec3 position, glm::vec3 rotation) :
				position(position), rotation(rotation) {
	head = position + glm::vec3(0.0f, 2.0f, 0.0f);
	collider = new SphereCollider(head, 1.0f);
	camera = new PerspectiveCamera(75.0f, 800.0f/600.0f, 0.1f, 100.0f, head);
	accel = PLAYER_ACCEL_DEFAULT;
}

Player::~Player() {
	delete collider;
}

void Player::update(GLFWwindow* window, Shader& shader, float deltaTime, glm::vec2 mouseRelative) {
	camera->yaw += mouseRelative.x * deltaTime * 50.0f;
	camera->pitch -= mouseRelative.y * deltaTime * 50.0f;
	camera->pitch = glm::clamp(camera->pitch, -89.0f, 89.0f);
	camera->updateCameraVectors();
	direction = {0.0f, 0.0f, 0.0f};
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		direction.z -= 1.0f;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		direction.z += 1.0f;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		direction.x -= 1.0f;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		direction.x += 1.0f;
	
	direction = glm::rotateY(direction, glm::radians(camera->yaw));
	velocity = glm::mix(velocity, direction * PLAYER_SPEED, accel * deltaTime);
	
	position += velocity;
	
	head = position + glm::vec3(0.0f, 5.0f, 0.0f);
	camera->position = head;
	collider->position = head;
	camera->use(shader);
}