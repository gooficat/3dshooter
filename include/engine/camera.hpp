#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/shader.hpp"

class Camera {
public:
    // Constructor
    Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
           const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f, float pitch = 0.0f);

    // Get view matrix
    glm::mat4 getViewMatrix() const;

    // Get projection matrix (to be implemented by subclasses)
    virtual glm::mat4 getProjectionMatrix() const = 0;

    // Use the camera (update view and projection matrices in the shader)
    virtual void use(Shader& shader) const;

    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler angles
    float yaw;
    float pitch;

protected:
    // Update camera vectors based on yaw and pitch angles
    void updateCameraVectors();
};

class PerspectiveCamera : public Camera {
public:
    // Constructor
    PerspectiveCamera(float fov, float aspectRatio, float near, float far,
                      const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                      const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
                      float yaw = -90.0f, float pitch = 0.0f);

    // Get projection matrix
    glm::mat4 getProjectionMatrix() const override;

    // Setters
    void setFOV(float fov);
    void setAspectRatio(float aspectRatio);
    void setNear(float near);
    void setFar(float far);

private:
    // Projection properties
    float fov;
    float aspectRatio;
    float near;
    float far;

    // Update projection matrix
    void updateProjectionMatrix();
};

#endif