#pragma once


#include <glm/glm/vec3.hpp>
#include <glm/glm/glm.hpp>
#include <vector>

namespace Murat{

    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };


    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 25.0f;
    const float SENSITIVITY = 0.1f;
    const float FOV = 45.0f;

    class Camera {
    private:
        /* Camera Attributes */
        glm::vec3 m_Position{};
        glm::vec3 m_Front;
        glm::vec3 m_Up{};
        glm::vec3 m_Right{};
        glm::vec3 m_WorldUp{};

        /* Euler Angles */
        float m_Yaw;
        float m_Pitch;

        /* Camera options */
        float m_MovementSpeed;
        float m_MouseSensitivity;
        float m_Fov;
    public:
        /* Constructor with vectors */
        explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = YAW, float pitch = PITCH);

        /* Constructor with scalar values */
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        /* Returns the view matrix calculated using Euler Angles and the LookAt Matrix */
        glm::mat4 getViewMatrix();

        /* Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems) */
        void processKeyboard(Camera_Movement direction, float deltaTime);

        /* Processes input received from a mouse input system. Expects the offset value in both the x and y direction. */
        void processMouseMovement(float offsetX, float offsetY, bool constrainPitch = true);

        /* Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis */
        void processMouseScroll(float offsetY);

        inline float getFov() const { return m_Fov; }

        inline glm::vec3 getPosition() const { return m_Position; }


    private:
        /* Calculates the front vector from the Camera's (updated) Euler Angles */
        void updateCameraVectors();
    };
}
