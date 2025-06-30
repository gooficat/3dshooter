#include "player.hpp"

float PLAYER_ACCEL_DEFAULT = 13.0f;
float PLAYER_SPEED = 7.0f;

Player::Player(glm::vec3 position, glm::vec3 rotation) :
				position(position), rotation(rotation) {
	collider = new SphereCollider(glm::vec3(0.0f, 1.5f, 0.0f), 1.0f);
	camera = new PerspectiveCamera(75.0f, 800.0f/600.0f, 0.1f, 1000.0f, head);
	accel = PLAYER_ACCEL_DEFAULT;
}

Player::~Player() {
	delete collider;
}

void Player::update(GLFWwindow* window, Shader& shader, float deltaTime, glm::vec2 mouseRelative) {
	camera->yaw += mouseRelative.x * deltaTime * 50.0f;
	camera->pitch -= mouseRelative.y * deltaTime * 50.0f;
	camera->updateCameraVectors();
	direction = glm::vec3(0.0f);
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		direction += camera->front;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		direction -= camera->front;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		direction -= glm::normalize(glm::cross(camera->front, camera->up));
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		direction += glm::normalize(glm::cross(camera->front, camera->up));
	
	direction.y = 0;
	//direction = glm::rotateY(direction, glm::radians(camera->yaw));
	velocity = direction;
	
	position += velocity;
	
	camera->position =  position + glm::vec3(0.0f, 1.5f, 0.0f);
	collider->position =  position + glm::vec3(0.0f, 1.0f, 0.0f);
	camera->use(shader);
}