#ifndef H_CAMERA_H
#define H_CAMERA_H

#include "common.h"

class Camera{
public:
	vec3 position;
	vec3 u, v, w;
	float fov;
	vec2 resolution;

public:
	Camera();

	void Init(vec3 p, vec3 uu, vec3 vv, vec3 ww, float fieldOfView, vec2 res);
	void Lookat(const vec3& eye_pos, const vec3& dest, const vec3& up);
	mat4 GetProjection() const;
	mat4 GetView() const;
};

#endif