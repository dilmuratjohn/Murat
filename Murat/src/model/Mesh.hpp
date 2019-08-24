#ifndef M_MESH_HPP
#define M_MESH_HPP

#include <render/Renderer.hpp>
#include <muratpch.hpp>

namespace Murat {

    struct struct_Vertex {
        glm::vec3 position;
        glm::vec3 normal;
    };

    class Mesh {
    public:
        std::vector<struct_Vertex> m_vertices;
        std::vector<unsigned int> m_indices;

    public:
        Mesh(std::vector<struct_Vertex>& vertices, std::vector<unsigned int>& indices);

        ~Mesh() = default;

        void draw(const std::shared_ptr<Shader>& shader);

    private:
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;

    private:
        void init();
    };

}

#endif
