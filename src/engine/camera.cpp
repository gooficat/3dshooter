#include "engine/camera.hpp"

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f)) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::use(Shader& shader) const {
    shader.setMat4("view", getViewMatrix());
    shader.setMat4("projection", getProjectionMatrix());
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far,
                                     const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
    : Camera(position, up, yaw, pitch), fov(fov), aspectRatio(aspectRatio), near(near), far(far) {
    updateProjectionMatrix();
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

void PerspectiveCamera::setFOV(float fov) {
    this->fov = fov;
    updateProjectionMatrix();
}

void PerspectiveCamera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
    updateProjectionMatrix();
}

void PerspectiveCamera::setNear(float near) {
    this->near = near;
    updateProjectionMatrix();
}

void PerspectiveCamera::setFar(float far) {
    this->far = far;
    updateProjectionMatrix();
}

void PerspectiveCamera::updateProjectionMatrix() {
    //this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->aspectRatio, this->near, this->far);
}
