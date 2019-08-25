#ifndef M_CAMERA_HPP
#define M_CAMERA_HPP

#include <glm/glm/vec3.hpp>
#include <glm/glm/glm.hpp>
#include <muratpch.hpp>

namespace Murat {

    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    const float ASPECT_RATIO = (float) SCR_WIDTH / (float) SCR_HEIGHT;
    const float NEAR_PLANE = 0.1f;
    const float FAR_PLANE = 100.0f;
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 5.0f;
    const float SENSITIVITY = 0.1f;
    const float FOV = 45.0f;

    class Camera {

    public:
        explicit Camera(glm::vec3 position = {0.0f, 0.0f, 0.0f}, glm::vec3 up = {0.0f, 1.0f, 0.0f},
                        float yaw = YAW, float pitch = PITCH);

        inline glm::mat4 getProjectionMatrix() { return m_ProjectionMatrix; }

        inline glm::mat4 getViewMatrix() { return m_ViewMatrix; }

        inline glm::mat4 getProjectionViewMatrix() { return m_ProjectionViewMatrix; }

        inline void setPosition(glm::vec3 position) {
            m_Position = position;
            this->update();
        }

        [[nodiscard]] inline glm::vec3 getPosition() const { return m_Position; }

        void move(Camera_Movement direction, float deltaTime);

        void rotate(float offsetX, float offsetY, bool constrainPitch = true);

        void scroll(float offset);

    private:


        void update();


    private:
        glm::mat4 m_ProjectionMatrix{};
        glm::mat4 m_ViewMatrix{};
        glm::mat4 m_ProjectionViewMatrix{};

        glm::vec3 m_Position{};
        glm::vec3 m_Front{};
        glm::vec3 m_Up{};
        glm::vec3 m_Right{};
        glm::vec3 m_WorldUp{};

        float m_Yaw;
        float m_Pitch;

        float m_MovementSpeed;
        float m_MouseSensitivity;
        float m_Fov;

    };
}


#endif