#ifndef H_SCENE_H
#define H_SCENE_H

#include "common.h"
#include "mesh.h"
#include "camera.h"

class Scene{
public:
	vector<Mesh> meshes;
	Camera camera;
	Texture bakeData;
	int width, height;
	bool showDiffuse = true;
	bool showLightmap = true;

public:
	virtual void Init() = 0;
	void Draw(Texture& bakeData);
};

#endif