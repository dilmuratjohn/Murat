#include <Murat.hpp>
#include <memory>
#include <glm/glm/gtc/type_ptr.hpp>

int main(int argc, char *argv[]) {
    auto *app = new Murat::Application();

    class ExampleLayer : public Murat::Layer {
    public:
        ExampleLayer() : Layer("Triangle") {
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

            m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
            m_VAO = std::make_unique<VertexArray>();
            m_IBO = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
            m_Shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource, "");
            VertexBufferLayout bufferLayout = VertexBufferLayout();
            bufferLayout.push<float>(4);
            m_VAO->addBuffer(*m_VBO, bufferLayout);

        }

        void onUpdate(Murat::TimeStep ts) override {
            Render::clear();
            Render::setClearColor(m_BackgroundColor);
            m_Shader->setUniform4f("u_Color", m_TriangleColor);
            Render::draw(*m_VAO, *m_IBO, *m_Shader);
        }

        void onImGuiRender() override {
            ImGui::Begin("Settings");
            ImGui::ColorEdit4("Background Color", glm::value_ptr(m_BackgroundColor));
            ImGui::ColorEdit4("Triangle Color", glm::value_ptr(m_TriangleColor));
            ImGui::End();
        }

    private:

        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<VertexBuffer> m_VBO;
        glm::vec4 m_BackgroundColor = {0.3f, 0.5f, 0.7f, 0.9f};
        glm::vec4 m_TriangleColor = {0.9f, 0.7f, 0.5f, 0.1f};
    };


    ExampleLayer layer = ExampleLayer();
    app->pushLayer(&layer);
    app->run();
    return 0;
}
