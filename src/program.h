#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>

using namespace std;
using namespace glm;

enum{
	EVertexShader = 0,
	EGeoShader,
	EFragShader,
	ENumShader,
};

class Program{
public:

protected:
	GLuint id;
	string source[ENumShader];

public:
	Program();
	void Init();
	GLuint CreateShader(GLuint id, string code);
	void SetSource(int id, string str);
	void Bind() const;
	void UnBind() const;

	void SetBool(const string& name, bool value) const;
	void SetInt(const string& name, int value) const;
	void SetFloat(const string& name, float value) const;
	void SetVec2(const string& name, vec2& value) const;
	void SetVec2(const string& name, float x, float y) const;
	void SetVec3(const string& name, vec3& value) const;
	void SetVec3(const string& name, float x, float y, float z) const;
	void SetVec4(const string& name, vec4& value) const;
	void SetVec4(const string& name, float x, float y, float z, float w) const;
	void SetMat4(const string& name, mat4& value) const;
	void SetMat4(const string& name, float value[16]) const;
};