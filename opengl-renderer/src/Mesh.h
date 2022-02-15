#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>

//#include "Shader.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;

    //// tangent
    //glm::vec3 Tangent;
    //// bitangent
    //glm::vec3 Bitangent;
    ////bone indexes which will influence this vertex
    //int m_BoneIDs[MAX_BONE_INFLUENCE];
    ////weights from each bone
    //float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {

public:
    // mesh Data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    unsigned int VAO;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void setupMesh();
    void draw();

private:
    // render data 
    unsigned int VBO, EBO;
};