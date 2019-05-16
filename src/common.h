#ifndef H_COMMON_H
#define H_COMMON_H

#include <vector>
#include <gl\glew.h>
#include <gl\glut.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

using namespace std;
using namespace glm;

inline bool IsBlack(vec3 c){
	return (c.x == 0.f) && (c.y == 0.f) && (c.z == 0.f);
}

#endif