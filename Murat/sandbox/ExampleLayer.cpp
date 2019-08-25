//
// Created by Murat on 2019/8/25.
//

#include "ExampleLayer.hpp"

namespace Sandbox {

    ExampleLayer::ExampleLayer() : Layer("Example") {

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
        Murat::Ref <Murat::IndexBuffer> indexBuffer;
        Murat::Ref <Murat::VertexBuffer> vertexBuffer;
        vertexBuffer = std::make_shared<Murat::VertexBuffer>(vertices, sizeof(vertices));
        m_VertexArray = std::make_shared<Murat::VertexArray>();
        indexBuffer = std::make_shared<Murat::IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
        m_Shader = std::make_shared<Murat::Shader>("res/shader/example.glsl");
        Murat::VertexBufferLayout bufferLayout = Murat::VertexBufferLayout();
        bufferLayout.push<float>(4);
        vertexBuffer->setLayout(bufferLayout);
        m_VertexArray->addVertexBuffer(vertexBuffer);
        m_VertexArray->setIndexBuffer(indexBuffer);
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
        Murat::RenderCommand::setClearColor(m_BackgroundColor);
        Murat::Renderer::beginScene(m_Camera);
        m_Shader->bind();
        m_Shader->setUniform4f("u_Color", m_RectangleColor);
        Murat::Renderer::submit(m_Shader, m_VertexArray, m_Transform);
        Murat::Renderer::endScene();
    }

    void ExampleLayer::onEvent(Murat::Event &e) {
    }

    void ExampleLayer::onImGuiRender() {
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Background Color", glm::value_ptr(m_BackgroundColor));
        ImGui::ColorEdit4("Rectangle Color", glm::value_ptr(m_RectangleColor));
        ImGui::End();
    }

}