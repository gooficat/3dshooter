#ifndef COLLIDER
#define COLLIDER
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/clamp.hpp>


class Collider {
public:
	glm::vec3 position;
	Collider(glm::vec3 position);
	virtual bool isColliding(Collider& other);
};

class SphereCollider : public Collider {
public:
	float radius;
	SphereCollider(glm::vec3 position, float radius);
	bool isColliding(Collider& other) override;
};

class BoundingBoxCollider : public Collider {
	glm::vec3 nPoint, pPoint;
	BoundingBoxCollider(glm::vec3 position, glm::vec3 nPoint, glm::vec3 pPoint);
	bool isColliding(Collider& other) override;
};



#endif