#include "texture3d.h"

void Texture3D::Init(int size){
	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_3D, id);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int numVoxels = size*size*size;
	GLubyte* data = new GLubyte[numVoxels * 4];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				unsigned char r = float(rand()) / RAND_MAX * 255;
				unsigned char g = float(rand()) / RAND_MAX * 255;
				unsigned char b = float(rand()) / RAND_MAX * 255;
				/*if (i == 64 && j==64 && k==64){
					data[4 * (i + j * size + k * size * size)] = r;
					data[4 * (i + j * size + k * size * size) + 1] = g;
					data[4 * (i + j * size + k * size * size) + 2] = b;
					data[4 * (i + j * size + k * size * size) + 3] = 255;
				}
				else*/{
					data[4 * (i + j * size + k * size * size)] = 0;
					data[4 * (i + j * size + k * size * size) + 1] = 0;
					data[4 * (i + j * size + k * size * size) + 2] = 0;
					data[4 * (i + j * size + k * size * size) + 3] = 0;
				}
			}
		}
	}

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, size, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	delete[] data;

	glGenerateMipmap(GL_TEXTURE_3D);
}