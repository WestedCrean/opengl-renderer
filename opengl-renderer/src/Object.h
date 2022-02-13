#pragma once
#include <string>
#include <vector>

#include "Shader.h"

class Object {

public:
	//vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	//vector<Mesh>    meshes;
	std::string path;
	//bool gammaCorrection;

	Object();
	Object(std::string path);

	void draw(Shader shader);
};

