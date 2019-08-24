#include "Renderer.hpp"
#include "RenderCommand.hpp"

namespace Murat {

    Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::beginScene(Camera &camera) {
        RenderCommand::clear();
        RenderCommand::setClearColor(glm::vec4(0.1,0.3,0.5,0.7));
        s_SceneData->ViewProjectionMatrix = camera.getViewMatrix();
    }

    void Renderer::endScene() {
    }

    void Renderer::submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray,
                          const glm::mat4 &transform) {
        shader->bind();
        shader->setUniformMat4f("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->setUniformMat4f("u_Transform", transform);
        vertexArray->bind();
        RenderCommand::draw(vertexArray);
    }

}