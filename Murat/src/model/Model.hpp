#ifndef M_MODEL_HPP
#define M_MODEL_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.hpp"

namespace Murat {


    class Model {

    public:
        explicit Model(std::string const &path);

        void draw(const std::shared_ptr <Shader> &shader);

    private:
        void init(std::string const &path);

        void processNode(aiNode *node, const aiScene *scene);

        Mesh *processMesh(aiMesh *mesh, const aiScene *scene);

    public:
        std::vector<Mesh *> m_Meshes;
    };

}
#endif
