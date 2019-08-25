#include <core/Log.hpp>
#include "Model.hpp"

namespace Murat {
    Model::Model(std::string const &path) {
        init(path);
    }

    void Model::init(std::string const &path) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path,
                                                 aiProcess_Triangulate | aiProcess_FlipUVs |
                                                 aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            Log_Error("[Assimp Error] ", importer.GetErrorString());
            return;
        }
        processNode(scene->mRootNode, scene);
    }

    void Model::draw(const std::shared_ptr <Shader> &shader) {
        for (auto &mesh : m_Meshes)
            mesh->draw(shader);
    }

    void Model::processNode(aiNode *node, const aiScene *scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(processMesh(mesh, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene) {

        std::vector <struct_Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            struct_Vertex vertex{};
            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        return new Mesh(vertices, indices);
    }
}
