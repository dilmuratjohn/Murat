#ifndef M_RENDER_HPP
#define M_RENDER_HPP

#include "FrameBuffer.hpp"
#include "RenderBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace Murat {

    class Render {

    public:
        static void clear();

        static void setClearColor(const glm::vec4 &color);

        static void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader);

        static void draw(const FrameBuffer &fb, const VertexArray &va, const IndexBuffer &ib, const Shader &shader);
    };
}

#endif
