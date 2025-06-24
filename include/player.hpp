#ifndef PLAYER_HPP
#define PLAYER_HPP

static const float GRAVITY;
static const float PLAYER_SPEED, PLAYER_ACCEL_DEFAULT, PLAYER_ACCEL_AIR, PLAYER_JUMP_VELOCITY;
static const float CAM_ACCEL, MOUSE_SENS;
static float player_accel;



class Player {
public:
	Collider* collider;
	Camera* camera;
	glm::vec3 position, rotation, velocity;
	Player(glm::vec3 position, glm::vec3 rotation);
	
	void update(float delta, glm::vec2 mouse_offset);
private:
};


#endif