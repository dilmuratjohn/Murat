#ifndef M_RENDER_HPP
#define M_RENDER_HPP

#include <core/Camera.hpp>
#include "FrameBuffer.hpp"
#include "RenderBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace Murat {

    class Renderer {

    public:
        static void beginScene(Camera &camera);

        static void endScene();

        static void submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData *s_SceneData;
    };
}

#endif
