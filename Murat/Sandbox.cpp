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

            m_VBO = std::make_unique<Murat::VertexBuffer>(vertices, sizeof(vertices));
            m_VAO = std::make_unique<Murat::VertexArray>();
            m_IBO = std::make_unique<Murat::IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
            m_Shader = std::make_unique<Murat::Shader>(vertexShaderSource, fragmentShaderSource, "");
            Murat::VertexBufferLayout bufferLayout = Murat::VertexBufferLayout();
            bufferLayout.push<float>(4);
            m_VAO->addBuffer(*m_VBO, bufferLayout);

        }

        void onUpdate(Murat::TimeStep ts) override {
            Murat::Render::clear();
            Murat::Render::setClearColor(m_BackgroundColor);
            m_Shader->setUniform4f("u_Color", m_RectangleColor);
            Murat::Render::draw(*m_VAO, *m_IBO, *m_Shader);
        }

        void onImGuiRender() override {
            ImGui::Begin("Settings");
            ImGui::ColorEdit4("Background Color", glm::value_ptr(m_BackgroundColor));
            ImGui::ColorEdit4("Rectangle Color", glm::value_ptr(m_RectangleColor));
            ImGui::End();
        }

    private:

        std::unique_ptr<Murat::Shader> m_Shader;
        std::unique_ptr<Murat::VertexArray> m_VAO;
        std::unique_ptr<Murat::IndexBuffer> m_IBO;
        std::unique_ptr<Murat::VertexBuffer> m_VBO;
        glm::vec4 m_BackgroundColor = {0.3f, 0.5f, 0.7f, 0.9f};
        glm::vec4 m_RectangleColor = {0.9f, 0.7f, 0.5f, 0.1f};
    };


    ExampleLayer layer = ExampleLayer();
    app->pushLayer(&layer);
    app->run();
    return 0;
}
