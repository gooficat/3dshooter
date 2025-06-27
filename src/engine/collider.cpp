#include "engine/collider.hpp"

Collider::Collider(glm::vec3 position) : position(position) {}

bool Collider::isColliding(Collider& other) {
    if (SphereCollider* sphere = dynamic_cast<SphereCollider*>(&other)) {
		return glm::distance(position, sphere->position) < sphere->radius;
	}
	else if (BoundingBoxCollider* box = dynamic_cast<BoundingBoxCollider*>(&other)) {
		return (position.x > box->nPoint.x &&
				position.x < box->pPoint.x &&
				position.y > box->nPoint.y &&
				position.y < box->nPoint.y &&
				position.z > box->nPoint.z &&
				position.z < box->nPoint.z
				);
	}
	else {
		return position == other.position;
	}
	return false;
}

SphereCollider::SphereCollider(glm::vec3 position, float radius) : Collider(position), radius(radius) {}


bool SphereCollider::isColliding(Collider& other) {
    if (SphereCollider* sphere = dynamic_cast<SphereCollider*>(&other)) {
		return glm::distance(position, sphere->position) < sphere->radius + radius;
	}
	else if (BoundingBoxCollider* box = dynamic_cast<BoundingBoxCollider*>(&other)) {
		glm::vec3 closestPoint = glm::clamp(position, box->nPoint, box->pPoint);
	}
	else {
		return glm::distance(position, other.position) < radius;
	}
	return false;
}

bool BoundingBoxCollider::isColliding(Collider& other) {
    if (dynamic_cast<SphereCollider*>(&other)) {
		
	}
	else if (dynamic_cast<BoundingBoxCollider*>(&other)) {
		
	}
	else {
		
	}
	return false;
}