#include <Murat.hpp>
#include <memory>
#include <glm/glm/gtc/type_ptr.hpp>

int main(int argc, char *argv[]) {
    auto *app = new Murat::Application();

    class ExampleLayer : public Murat::Layer {
    public:
        ExampleLayer() : Layer("Example") {

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
            std::shared_ptr<Murat::IndexBuffer> indexBuffer;
            std::shared_ptr<Murat::VertexBuffer> vertexBuffer;
            vertexBuffer = std::make_shared<Murat::VertexBuffer>(vertices, sizeof(vertices));
            m_VertexArray = std::make_shared<Murat::VertexArray>();
            indexBuffer = std::make_shared<Murat::IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
            m_Shader = std::make_shared<Murat::Shader>("res/shader/example.glsl");
            Murat::VertexBufferLayout bufferLayout = Murat::VertexBufferLayout();
            bufferLayout.push<float>(4);
            vertexBuffer->setLayout(bufferLayout);
            m_VertexArray->addVertexBuffer(vertexBuffer);
            m_VertexArray->setIndexBuffer(indexBuffer);
        }

        void onUpdate(Murat::TimeStep ts) override {
            Murat::RenderCommand::clear();
            Murat::RenderCommand::setClearColor(m_BackgroundColor);
            Murat::Renderer::beginScene(camera);
            m_Shader->bind();
            m_Shader->setUniform4f("u_Color", m_RectangleColor);
            Murat::Renderer::submit(m_Shader, m_VertexArray);
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
        std::shared_ptr<Murat::VertexArray> m_VertexArray;
        glm::vec4 m_BackgroundColor = {0.3f, 0.5f, 0.7f, 0.9f};
        glm::vec4 m_RectangleColor = {0.9f, 0.7f, 0.5f, 0.1f};
        Murat::Camera camera = Murat::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    };

    ExampleLayer layer = ExampleLayer();
    app->pushLayer(&layer);
    app->run();
    return 0;
}
