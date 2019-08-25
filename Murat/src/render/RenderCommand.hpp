//
// Created by Murat on 2019/8/24.
//

#ifndef M_RENDER_COMMAND_HPP
#define M_RENDER_COMMAND_HPP

#include <glm/glm.hpp>
#include <muratpch.hpp>
#include "VertexArray.hpp"

namespace Murat {
    class RenderCommand {
    public:
        inline static void clear() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        };

        inline static void setClearColor(const glm::vec4 &color = glm::vec4(0.2f, 0.3f, 0.5f, 0.7f)) {
            glClearColor(color.r, color.g, color.b, color.a);
        }

        inline static void draw(const std::shared_ptr<VertexArray> &vertexArray) {
            glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
        }

    };
}

#endif
