//
// Created by Murat on 2019/8/25.
//

#include "ExampleLayer.hpp"

namespace Sandbox {

    ExampleLayer::ExampleLayer() : Layer("Example") {

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        float vertices[6 * 4] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f
        };

        Murat::Ref <Murat::IndexBuffer> indexBuffer;
        Murat::Ref <Murat::VertexBuffer> vertexBuffer;
        vertexBuffer = std::make_shared<Murat::VertexBuffer>(vertices, sizeof(vertices));
        indexBuffer = std::make_shared<Murat::IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));

        m_VertexArray = std::make_shared<Murat::VertexArray>();
        m_Shader = std::make_shared<Murat::Shader>("asset/shader/example.glsl");
        Murat::VertexBufferLayout bufferLayout = Murat::VertexBufferLayout();
        bufferLayout.push<float>(4);
        bufferLayout.push<float>(2);

        vertexBuffer->setLayout(bufferLayout);
        m_VertexArray->addVertexBuffer(vertexBuffer);
        m_VertexArray->setIndexBuffer(indexBuffer);

        m_LogoTexture = Murat::Texture2D::create("asset/texture/murat_logo.png");
        m_BackgroundTexture = Murat::Texture2D::create("asset/texture/checkerboard.png");

        m_Camera.setPosition({0.0f, 0.0f, 3.0f});

    }

    void ExampleLayer::onUpdate(Murat::TimeStep deltaTime) {

        if (Murat::Input::isKeyPressed(MURAT_KEY_W))
            m_Camera.move(Murat::Camera_Movement::FORWARD, deltaTime);

        else if (Murat::Input::isKeyPressed(MURAT_KEY_S))
            m_Camera.move(Murat::Camera_Movement::BACKWARD, deltaTime);

        if (Murat::Input::isKeyPressed(MURAT_KEY_A))
            m_Camera.move(Murat::Camera_Movement::LEFT, deltaTime);

        else if (Murat::Input::isKeyPressed(MURAT_KEY_D))
            m_Camera.move(Murat::Camera_Movement::RIGHT, deltaTime);

        if (Murat::Input::isKeyPressed(MURAT_KEY_UP))
            m_Camera.move(Murat::Camera_Movement::UP, deltaTime);

        else if (Murat::Input::isKeyPressed(MURAT_KEY_DOWN))
            m_Camera.move(Murat::Camera_Movement::DOWN, deltaTime);

        Murat::RenderCommand::clear();
        Murat::RenderCommand::setClearColor(m_ClearColor);
        Murat::Renderer::beginScene(m_Camera);
        m_Shader->bind();
        m_Shader->setUniform4f("u_Color", m_BackgroundColor);
        m_BackgroundTexture->bind(0);
        Murat::Renderer::submit(m_Shader, m_VertexArray, m_Transform);
        m_Shader->setUniform4f("u_Color", m_LogoColor);
        m_LogoTexture->bind(0);
        Murat::Renderer::submit(m_Shader, m_VertexArray, m_Transform);
        Murat::Renderer::endScene();
    }

    void ExampleLayer::onEvent(Murat::Event &e) {
    }

    void ExampleLayer::onImGuiRender() {
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Logo Color", glm::value_ptr(m_LogoColor));
        ImGui::ColorEdit4("Background Color", glm::value_ptr(m_BackgroundColor));
        ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_ClearColor));
        ImGui::End();
    }

}
