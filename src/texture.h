#ifndef H_TEXTURE_H
#define H_TEXTURE_H

#include "common.h"

class Texture{
public:
	GLuint tex;
	bool valid = false;
	int width, height;

public:
	void Init(const char* filename);

	void Bind(int unit) const;
	void UnBind() const;

private:
	bool loadTexture(const char* filename, int& width, int& height, bool srgb, vector<vec4>& output);
	bool loadExr(const char* filename, int& width, int& height, vector<vec4>& output);
};

#endif