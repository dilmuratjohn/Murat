#include <glm/glm/ext.hpp>
#include "Camera.hpp"


Murat::Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        :
        m_Position(position),
        m_WorldUp(up),
        m_Yaw(yaw),
        m_Pitch(pitch),
        m_Front({0.0f, 0.0f, -1.0f}),
        m_MovementSpeed(SPEED),
        m_MouseSensitivity(SENSITIVITY),
        m_Fov(FOV) {
    this->update();
}

void Murat::Camera::move(Camera_Movement direction, float deltaTime) {
    float velocity = m_MovementSpeed * deltaTime;
    switch (direction) {
        case FORWARD:
            m_Position += m_Front * velocity;
            break;
        case BACKWARD:
            m_Position -= m_Front * velocity;
            break;
        case LEFT:
            m_Position -= m_Right * velocity;
            break;
        case RIGHT:
            m_Position += m_Right * velocity;
            break;
        case UP:
            m_Position += m_WorldUp * velocity;
            break;
        case DOWN:
            m_Position -= m_WorldUp * velocity;
            break;
    }
    this->update();

}

void Murat::Camera::rotate(float offsetX, float offsetY, bool constrainPitch) {
    offsetX *= m_MouseSensitivity;
    offsetY *= m_MouseSensitivity;

    m_Yaw += offsetX;
    m_Pitch += offsetY;

    if (constrainPitch) {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        else if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }

    this->update();
}

void Murat::Camera::scroll(float offset) {
    if (m_Fov >= 1.0f && m_Fov <= 75.0f)
        m_Fov -= offset;
    else if (m_Fov <= 1.0f)
        m_Fov = 1.0f;
    else if (m_Fov >= 75.0f)
        m_Fov = 75.0f;
}

void Murat::Camera::update() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
    m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

