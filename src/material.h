#ifndef H_MATERIAL_H
#define H_MATERIAL_H

#include "common.h"
#include "texture.h"

class Program;
class Material{
public:
	vec3 emission;
	vec3 diffuse;
	Texture texDiffuse;
	bool isConstant;

public:
	void Init(const char* diffusePath);
	void Bind(Program& program);
};

#endif