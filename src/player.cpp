#include "player.hpp"

float GRAVITY = 9.8f;
float PLAYER_ACCEL_DEFAULT = 7.0f;
float PLAYER_SPEED = 4.0f;

Player::Player(glm::vec3 position, glm::vec3 rotation) :
				position(position), rotation(rotation) {
	collider = new SphereCollider(glm::vec3(0.0f, 1.5f, 0.0f), 1.0f);
	camera = new PerspectiveCamera((float)M_PI*2.0f/3.0f, 800.0f/600.0f, 0.1f, 1000.0f, head);
	accel = PLAYER_ACCEL_DEFAULT;
}

Player::~Player() {
	delete collider;
}

void Player::update(GLFWwindow* window, Shader& shader, float deltaTime, glm::vec2 mouseRelative) {
	camera->yaw += mouseRelative.x * deltaTime * 0.2f;
	camera->pitch -= mouseRelative.y * deltaTime * 0.2f;
	camera->pitch = glm::clamp(camera->pitch, -(float)M_PI/2, (float)M_PI/2);
	camera->updateCameraVectors();
	direction = glm::vec3(0.0f);
	forward = glm::normalize(glm::vec3(camera->front.x, 0.0f, camera->front.z));
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		direction += forward;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		direction -= forward;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		direction -= glm::normalize(glm::cross(forward, camera->up));
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		direction += glm::normalize(glm::cross(forward, camera->up));
	
	direction.y = 0;
	//direction = glm::rotateY(direction, glm::radians(camera->yaw));
	velocity = glm::mix(velocity, direction * PLAYER_SPEED, accel * deltaTime);
	
	camera->use(shader);
}

void Player::move_and_collide(std::vector<Collider>& colliders, float deltaTime) {
	//velocity.y -= GRAVITY;
	position.x += velocity.x;

	
	camera->position =  position + glm::vec3(0.0f, 1.5f, 0.0f);
	collider->position =  position + glm::vec3(0.0f, 1.0f, 0.0f);
}