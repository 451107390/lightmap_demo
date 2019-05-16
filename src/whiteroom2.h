#ifndef H_WHITEROOM_SCENE_H
#define H_WHITEROOM_SCENE_H

#include "common.h"
#include "scene.h"

class WhiteroomScene : public Scene{
public:
	WhiteroomScene(){
		width = 512;
		height = 512;
	}

	virtual void Init(){
		width = 512;
		height = 512;
		bakeData.Init("whiteroom2/bakedata0.exr");

		Mesh floor;
		floor.Load("whiteroom2/geometry/WhiteRoom.fbx");
		Material floor_material;
		floor_material.emission = vec3(0.f);
		floor_material.diffuse = vec3(0.7, 0.7, 0.7);
		floor_material.Init(nullptr);
		floor.material = floor_material;
		meshes.push_back(floor);

		camera.Init(vec3(0, 1.0, 12), vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f),
			vec3(0.f, 0.f, 1.f), 60.f, vec2(width, height));
	}
};

#endif