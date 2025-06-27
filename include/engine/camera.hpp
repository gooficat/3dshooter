#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/shader.hpp"

class Camera {
public:
    Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
           const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f, float pitch = 0.0f);

    glm::mat4 getViewMatrix() const;
    virtual glm::mat4 getProjectionMatrix() const = 0;

    virtual void use(Shader& shader) const;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    void updateCameraVectors();
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fov, float aspectRatio, float near, float far,
                      const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                      const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
                      float yaw = -90.0f, float pitch = 0.0f);

    glm::mat4 getProjectionMatrix() const override;

    float fov;
    float aspectRatio;
    float near;
    float far;

    void updateProjectionMatrix();
};

#endif