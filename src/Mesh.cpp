#include <iostream>
#include <fstream>
#include <sstream>

#include "Mesh.hpp"
#include "Render.hpp"



Mesh::Mesh(std::vector<struct_Vertex> vertices, std::vector<unsigned int> indices, std::vector<struct_Texture> textures)
	:
	m_vertices(vertices),
	m_indices(indices),
	m_textures(textures)
{
	init();
}

void Mesh::draw(Shader shader)
{
	unsigned int diffuseNr  = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr   = 1;
	unsigned int heightNr   = 1;
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		std::string _number;
		std::string _name = m_textures[i].type;
		if (_name == "texture_diffuse")
			_number = std::to_string(diffuseNr++);
		else if (_name == "texture_specular")
			_number = std::to_string(specularNr++);
		else if (_name == "texture_normal")
			_number = std::to_string(normalNr++);
		else if (_name == "texture_height")
			_number = std::to_string(heightNr++);
		shader.setUniform1i((_name + _number).c_str(), i);
		m_textures[i].id->bind(i);
	}

	m_va->bind();
	Render::draw(*m_va, *m_ib, shader);
	m_va->unbind();
}

void Mesh::init()
{
	VertexArray _va;
	VertexBuffer _vb(&m_vertices[0], m_vertices.size() * sizeof(struct_Vertex));
	VertexBufferLayout _layout;
	IndexBuffer _ib(&m_indices[0], m_indices.size() * sizeof(unsigned int));
	_layout.push<float>((float)offsetof(struct_Vertex, normal));
	_layout.push<float>((float)offsetof(struct_Vertex, texcoords));
	_layout.push<float>((float)offsetof(struct_Vertex, tangent));
	_layout.push<float>((float)offsetof(struct_Vertex, bitangent));
	_va.addBuffer(_vb, _layout);
	m_va = &_va;
	m_vb = &_vb;
	m_ib = &_ib;
}
