#pragma once

#include "render/FrameBuffer.hpp"
#include "render/RenderBuffer.hpp"
#include "render/VertexArray.hpp"
#include "render/IndexBuffer.hpp"
#include "render/Shader.hpp"
#include "render/Texture.hpp"

namespace Render {
    void clear();

    void clear(const char color);

    void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader);

    void draw(const FrameBuffer &fb, const VertexArray &va, const IndexBuffer &ib, const Shader &shader);
}
