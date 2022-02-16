#pragma once
#include <string>
#include <vector>
#include <assimp/scene.h>

#include "Shader.h"
#include "Mesh.h"

class Object {

    public:
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string path;
    //bool gammaCorrection;
    std::string directory;

    Object();
    Object(const std::string& path);

    void draw(Shader& shader);

    private:
    void loadModel(const std::string& path);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    void processNode(aiNode* node, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

