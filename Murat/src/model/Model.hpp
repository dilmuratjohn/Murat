#pragma once

#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
    std::vector<Mesh *> meshes;

public:
    Model(std::string const &path);

    void draw(Shader &shader);

private:
    void init(std::string const &path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh *processMesh(aiMesh *mesh, const aiScene *scene);
};
