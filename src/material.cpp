#include "material.h"
#include "program.h"

void Material::Init(const char* diffusePath){
	isConstant = true;
	bool pass = (diffusePath == nullptr);
	if (!pass && strcmp(diffusePath, "") == 0){
		pass = true;
	}
	if (!pass){
		isConstant = false;
		texDiffuse.Init(diffusePath);
	}
}

void Material::Bind(Program& program){
	bool isLight = !IsBlack(emission);
	program.SetVec3("emission", emission);
	if (isLight) return;

	program.SetBool("isConstant", isConstant);
	if (isConstant)
		program.SetVec3("diffuse", diffuse);
	else{
		texDiffuse.Bind(1);
		program.SetInt("texDiffuse", 1);
	}
}