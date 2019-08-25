#include "Mesh.hpp"

namespace Murat {

    Mesh::Mesh(std::vector<struct_Vertex>& vertices, std::vector<unsigned int>& indices)
            : m_vertices(vertices),
              m_indices(indices) {
        init();
    }

    void Mesh::draw(const std::shared_ptr<Shader>& shader) {
        m_VertexArray->bind();
        Renderer::submit(shader, m_VertexArray);
    }

    void Mesh::init() {
        m_VertexArray  = std::make_shared<VertexArray>();
        m_VertexBuffer = std::make_shared<VertexBuffer>(&m_vertices[0], m_vertices.size() * sizeof(struct_Vertex));
        VertexBufferLayout _layout;
        m_IndexBuffer = std::make_shared<IndexBuffer>(&m_indices[0], m_indices.size() * sizeof(unsigned int));
        _layout.push<float>(3);
        _layout.push<float>(3);
        m_VertexBuffer->setLayout(_layout);
        m_VertexArray->addVertexBuffer(m_VertexBuffer);
        m_VertexArray->setIndexBuffer(m_IndexBuffer);
    }

}
