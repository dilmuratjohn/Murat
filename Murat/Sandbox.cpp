#include <Murat.hpp>
#include <memory>
#include <glm/glm/gtc/type_ptr.hpp>

int main(int argc, char *argv[]) {
    auto *app = new Murat::Application();

    class ExampleLayer : public Murat::Layer {
    public:
        ExampleLayer() : Layer("Example") {
            const std::string vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec4 a_Position;
            void main()
            {
                gl_Position = a_Position;
            }
            )";
            const std::string fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            uniform vec4 u_Color;
            void main()
            {
                FragColor = u_Color;
            }
            )";

            float vertices[4 * 4] = {
                    +0.5f, +0.5f, 0.0f, 1.0f,
                    +0.5f, -0.5f, 0.0f, 1.0f,
                    -0.5f, -0.5f, 0.0f, 1.0f,
                    -0.5f, +0.5f, 0.0f, 1.0f,
            };

            unsigned int indices[] = {
                    0, 1, 2,
                    2, 3, 0
            };

            m_VBO = std::make_shared<Murat::VertexBuffer>(vertices, sizeof(vertices));
            m_VAO = std::make_shared<Murat::VertexArray>();
            m_IBO = std::make_shared<Murat::IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
            m_Shader = std::make_shared<Murat::Shader>(vertexShaderSource, fragmentShaderSource, "");
            Murat::VertexBufferLayout bufferLayout = Murat::VertexBufferLayout();
            bufferLayout.push<float>(4);
            m_VBO->setLayout(bufferLayout);
            m_VAO->addVertexBuffer(m_VBO);
            m_VAO->setIndexBuffer(m_IBO);
        }

        void onUpdate(Murat::TimeStep ts) override {
            Murat::Renderer::beginScene(camera);
            m_Shader->setUniform4f("u_Color", m_RectangleColor);
            Murat::Renderer::submit(m_Shader, m_VAO);
            Murat::Renderer::endScene();

        }

        void onImGuiRender() override {
            ImGui::Begin("Settings");
            ImGui::ColorEdit4("Background Color", glm::value_ptr(m_BackgroundColor));
            ImGui::ColorEdit4("Rectangle Color", glm::value_ptr(m_RectangleColor));
            ImGui::End();
        }

    private:

        std::shared_ptr<Murat::Shader> m_Shader;
        std::shared_ptr<Murat::VertexArray> m_VAO;
        std::shared_ptr<Murat::IndexBuffer> m_IBO;
        std::shared_ptr<Murat::VertexBuffer> m_VBO;
        glm::vec4 m_BackgroundColor = {0.3f, 0.5f, 0.7f, 0.9f};
        glm::vec4 m_RectangleColor = {0.9f, 0.7f, 0.5f, 0.1f};
        Murat::Camera camera = Murat::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    };

    ExampleLayer layer = ExampleLayer();
    app->pushLayer(&layer);
    app->run();
    return 0;
}
