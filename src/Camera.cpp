#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Fov(FOV)
{
    m_Position = position;
    m_WorldUp = up;
    m_Yaw = yaw;
    m_Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Fov(FOV)
{
    m_Position = glm::vec3(posX, posY, posZ);
    m_WorldUp = glm::vec3(upX, upY, upZ);
    m_Yaw = yaw;
    m_Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = m_MovementSpeed * deltaTime;
    if (direction == FORWARD)
        m_Position += m_Front * velocity;
    if (direction == BACKWARD)
        m_Position -= m_Front * velocity;
    if (direction == LEFT)
        m_Position -= m_Right * velocity;
    if (direction == RIGHT)
        m_Position += m_Right * velocity;
    if (direction == UP)
        m_Position += m_WorldUp * velocity;
    if (direction == DOWN)
        m_Position -= m_WorldUp * velocity;

}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= m_MouseSensitivity;
    yoffset *= m_MouseSensitivity;

    m_Yaw   += xoffset;
    m_Pitch += yoffset;

    /* Make sure that when pitch is out of bounds, screen doesn't get flipped */
    if (constrainPitch)
    {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }

    /* Update Front, Right and Up Vectors using the updated Euler angles */
    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    if (m_Fov >= 1.0f && m_Fov <= 75.0f)
        m_Fov -= yoffset;
    if (m_Fov <= 1.0f)
        m_Fov = 1.0f;
    if (m_Fov >= 75.0f)
        m_Fov = 75.0f;
}

void Camera::updateCameraVectors()
{
    /* Calculate the new Front vector */
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    /* Also re-calculate the Right and Up vector */
    /* Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement. */
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up    = glm::normalize(glm::cross(m_Right, m_Front));
}

