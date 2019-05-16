#ifndef H_MESH_H
#define H_MESH_H

#include "common.h"
#include "material.h"
#include "program.h"

struct Vertex{
	vec3 v;
	vec3 n;
	vec2 uv;
};

class aiMesh;
class aiScene;
class aiNode;
class Camera;

class Mesh{
public:
	struct Vertex{
		vec3 pos;
		vec3 nor;
		vec2 uv;
		vec2 uv2;
	};

	vector<unsigned int> indices;
	vector<Vertex> vertices;


	GLuint vertexVbo, indexVbo;
	Material material;
	Program program;
	bool hasUV2 = false;

public:
	Mesh();
	~Mesh();

	bool Load(const char* file, float scale = 1.f);
	void Draw(Camera& camera, Texture& bakeData, bool showDiffuse, bool showLightmap);

private:
	void processMesh(aiMesh* aimesh, const aiScene* scene);
	void processNode(aiNode* node, const aiScene* scene);
	void generateLightMapUV();
};

#endif