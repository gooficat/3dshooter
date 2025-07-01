#include "engine/collider.hpp"

Collider::Collider(glm::vec3 position) : position(position) {}
BoundingBoxCollider::BoundingBoxCollider(glm::vec3 position, glm::vec3 nPoint, glm::vec3 pPoint) : Collider(position), nPoint(nPoint), pPoint(pPoint) {}
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
    if (SphereCollider* sphere = dynamic_cast<SphereCollider*>(&other)) {
		float x = std::max(nPoint.x, std::min(sphere->position.x, pPoint.x));
		float y = std::max(nPoint.y, std::min(sphere->position.y, pPoint.y));
		float z = std::max(nPoint.z, std::min(sphere->position.z, pPoint.z));
		
		float dist = std::sqrt(
			(x - sphere->position.x) * (x - sphere->position.x) +
			(y - sphere->position.y) * (y - sphere->position.y) + 
			(z - sphere->position.z) * (z - sphere->position.z)
		);
		
		return dist < sphere->radius;
	}
	else if (dynamic_cast<BoundingBoxCollider*>(&other)) {
		
	}
	else {
		return (other.position.x > nPoint.x &&
				other.position.x < pPoint.x &&
				other.position.y > nPoint.y &&
				other.position.y < nPoint.y &&
				other.position.z > nPoint.z &&
				other.position.z < nPoint.z
				);
	}
	return false;
}