#include "Renderer.hpp"
#include "RenderCommand.hpp"

namespace Murat {

    Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;



    void Renderer::beginScene(Camera &camera) {
        s_SceneData->ViewProjectionMatrix = camera.getProjectionViewMatrix();
    }

    void Renderer::endScene() {
    }

    void Renderer::submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray,
                          const glm::mat4 &transform) {
        shader->bind();
        shader->setUniformMat4f("u_ProjectionView", s_SceneData->ViewProjectionMatrix);
        shader->setUniformMat4f("u_Transform", transform);
        vertexArray->bind();
        RenderCommand::draw(vertexArray);
    }

}