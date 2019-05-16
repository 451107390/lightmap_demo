#ifndef H_FRAMEBUFFER_H
#define H_FRAMEBUFFER_h

#include "common.h"

class Framebuffer{
public:
	GLuint id, tex, depth;

public:
	void Init(int width, int height);

	void BindForWriting();
	void BindForReading(GLenum texUnit);
};

#endif