#pragma once

#include <render/Render.hpp>

struct struct_Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh {
public:
    std::vector<struct_Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

private:
    VertexArray *m_va;
    VertexBuffer *m_vb;
    IndexBuffer *m_ib;

public:
    Mesh(std::vector<struct_Vertex> vertices, std::vector<unsigned int> indices);

    ~Mesh();

    void draw(Shader &shader);

private:
    void init();
};
