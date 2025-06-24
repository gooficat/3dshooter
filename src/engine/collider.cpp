#include "engine/collider.hpp"

Collider::Collider(glm::vec3 position) : position(position) {}

bool Collider::isColliding(Collider& other) {
    if (dynamic_cast<SphereCollider*>(&other)) {
		return glm::distance(position, other.position) < other.radius;
	}
	else if (dynamic_cast<BoundingBoxCollider*>(&other)) {
		return (position.x > other.nPoint.x &&
				position.x < other.pPoint.x &&
				position.y > other.nPoint.y &&
				position.y < other.nPoint.y &&
				position.z > other.nPoint.z &&
				position.z < other.nPoint.z
				);
	}
	else {
		return position == other.position;
	}
	return false;
}

SphereCollider::SphereCollider(glm::vec3 position, float radius) : Collider(position), radius(radius) {}


bool SphereCollider::isColliding(Collider& other) {
    if (dynamic_cast<SphereCollider*>(&other)) {
		return glm::distance(position, other.position) < other.radius + radius;
	}
	else if (dynamic_cast<BoundingBoxCollider*>(&other)) {
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