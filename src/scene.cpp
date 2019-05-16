#include "scene.h"

void Scene::Draw(Texture& bakeData){
	for (int i = 0; i < meshes.size(); ++i){
		meshes[i].Draw(camera, bakeData, showDiffuse, showLightmap);
	}
}