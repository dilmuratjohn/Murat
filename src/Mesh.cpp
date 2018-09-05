#include "Mesh.hpp"


Mesh::Mesh(std::vector<struct_Vertex> vertices, std::vector<unsigned int> indices)
	:
	m_vertices(vertices),
	m_indices(indices)
{
	init();
}

void Mesh::draw(Shader &shader)
{
	m_va->bind();
	Render::draw(*m_va, *m_ib, shader);
}

void Mesh::init()
{
	VertexArray _va;
	VertexBuffer _vb(&m_vertices[0], m_vertices.size() * sizeof(struct_Vertex));
	VertexBufferLayout _layout;
	IndexBuffer _ib(&m_indices[0], m_indices.size() * sizeof(unsigned int));
	_layout.push<float>(3);
	_layout.push<float>(3);
	_va.addBuffer(_vb, _layout);
	m_va = &_va;
	m_vb = &_vb;
	m_ib = &_ib;
}
