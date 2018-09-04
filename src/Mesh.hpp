#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "Texture.hpp"


struct struct_Vertex
{
	glm::vec4 position;
	glm::vec4 normal;
	glm::vec2 texcoords;
	glm::vec4 tangent;
	glm::vec4 bitangent;
};

struct struct_Texture
{
	Texture::Texture2D* id;
	std::string type;
	std::string path;
};


class Mesh
{
public:

	std::vector<struct_Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<struct_Texture> m_textures;

private:

	VertexArray* m_va;
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;

public:
	Mesh(std::vector<struct_Vertex> vertices, std::vector<unsigned int> indices, std::vector<struct_Texture> textures);

	void draw(Shader shader);

private:

	void init();
};

#endif