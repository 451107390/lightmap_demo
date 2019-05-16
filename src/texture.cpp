#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>
#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"


void Texture::Init(const char* filename){
	string file = filename;
	string extension = file.substr(file.find_last_of('.'));
	vector<vec4> image;
	bool ret;
	if (extension == ".exr"){
		ret = loadExr(filename, width, height, image);
	}
	else{
		ret = loadTexture(filename, width, height, true, image);
	}
	if (!ret) return;

	vector<float> cc(width*height * 4);
	for (int s = 0; s < height; ++s){
		for (int t = 0; t < width; ++t){
			//flip
			int idx = s*width + t;
			int inverseIdx = (height - s - 1)*width + t;
			cc[4 * idx + 0] = image[idx].x;
			cc[4 * idx + 1] = image[idx].y;
			cc[4 * idx + 2] = image[idx].z;
			cc[4 * idx + 3] = image[idx].a;
		}
	}

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, &cc[0]);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	valid = true;
}

void Texture::Bind(int unit) const{
	if (!valid) return;
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, tex);
}

void Texture::UnBind() const{
	if (!valid) return;
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::loadTexture(const char* filename, int& width, int& height, bool srgb, vector<vec4>& output){
	int component;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* tex = stbi_load(filename, &width, &height, &component, 0);
	if (tex){
		output.resize(width*height);
		float inv = 1.f / 255.f;
		for (int s = 0; s < height; ++s){
			for (int t = 0; t < width; ++t){
				//flip
				int idx = s*width + t;
				//int inverseIdx = (height - s - 1)*width + t;

				vec4 texel;
				if (component == 1){
					float r = tex[idx] * inv;
					texel = vec4(r, r, r, 1.f);
				}
				else if (component == 3){
					float r = tex[3 * idx] * inv;
					float g = tex[3 * idx + 1] * inv;
					float b = tex[3 * idx + 2] * inv;
					texel = vec4(r, g, b, 1.f);
				}
				else if (component == 4){
					float r = tex[4 * idx] * inv;
					float g = tex[4 * idx + 1] * inv;
					float b = tex[4 * idx + 2] * inv;
					float a = tex[4 * idx + 3] * inv;
					texel = vec4(r, g, b, a);
				}

				//convert from srgb space to linear space
				if (srgb)
					output[idx] = vec4(powf(texel.r, 2.2f), powf(texel.g, 2.2f), powf(texel.b, 2.2f), texel.a);
				else
					output[idx] = texel;
			}
		}

		stbi_image_free(tex);
	}
	else
		return false;

	return true;
}

bool Texture::loadExr(const char* filename, int& width, int& height, vector<vec4>& output){
	const char* err = NULL; // or nullptr in C++11

	float* out;
	int ret = LoadEXR(&out, &width, &height, filename, &err);

	if (ret != TINYEXR_SUCCESS) {
		if (err) {
			fprintf(stderr, "ERR : %s\n", err);
			FreeEXRErrorMessage(err); // release memory of error message.
			return false;
		}
	}
	else {
		output.resize(width*height);
		/*for (int i = 0; i < height; ++i){
			for (int j = 0; j < width; ++j){
				int idx = i*width + j;
				int inverse = (height - i - 1)*width + j;
				float r = out[4 * idx + 0];
				float g = out[4 * idx + 1];
				float b = out[4 * idx + 2];
				output[inverse] = vec3(r, g, b);
			}
		}*/
		for (int i = 0; i < width*height; ++i){
			float r = out[4 * i + 0];
			float g = out[4 * i + 1];
			float b = out[4 * i + 2];
			output[i] = vec4(r, g, b, 1.f);
		}
		free(out); // relase memory of image data
	}

	return true;
}