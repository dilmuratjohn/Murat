#include "render/Render.hpp"

void Render::clear() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Render::setClearColor(const glm::vec4 &color) {
    GLCall(glClearColor(color.r, color.g, color.b, color.a));
}

void Render::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) {
    shader.bind();
    va.bind();
    ib.bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Render::draw(const FrameBuffer &fb, const VertexArray &va, const IndexBuffer &ib, const Shader &shader) {
    fb.bind();
    Render::draw(va, ib, shader);
    fb.unbind();
}