#include "Mesh.hpp"

namespace Murat {

    Mesh::Mesh(std::vector<struct_Vertex> vertices, std::vector<unsigned int> indices)
            : m_vertices(vertices),
              m_indices(indices) {
        init();
    }

    Mesh::~Mesh() {
        delete m_va;
        delete m_vb;
        delete m_ib;
    }

    void Mesh::draw(Shader &shader) {
        m_va->bind();
        Render::draw(*m_va, *m_ib, shader);
    }

    void Mesh::init() {
        m_va = new VertexArray();
        m_vb = new VertexBuffer(&m_vertices[0], m_vertices.size() * sizeof(struct_Vertex));
        VertexBufferLayout _layout;
        m_ib = new IndexBuffer(&m_indices[0], m_indices.size() * sizeof(unsigned int));
        _layout.push<float>(3);
        _layout.push<float>(3);
        m_va->addBuffer(*m_vb, _layout);
    }

}
