#include "Render.hpp"

namespace Murat {

    void Render::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Render::setClearColor(const glm::vec4 &color = glm::vec4(0.2f, 0.3f, 0.5f, 0.7f)) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Render::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) {
        shader.bind();
        va.bind();
        ib.bind();
        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Render::draw(const FrameBuffer &fb, const VertexArray &va, const IndexBuffer &ib, const Shader &shader) {
        fb.bind();
        Render::draw(va, ib, shader);
        fb.unbind();
    }

}