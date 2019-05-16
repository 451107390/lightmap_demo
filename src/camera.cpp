#include "camera.h"

Camera::Camera(){
	
}

void Camera::Init(vec3 p, vec3 uu, vec3 vv, vec3 ww, float fieldOfView, vec2 res){
	position = p;
	u = uu;
	v = vv;
	w = ww;
	fov = fieldOfView;
	resolution = res;
}

void Camera::Lookat(const vec3& eye_pos, const vec3& dest, const vec3& up){
	w = normalize(eye_pos - dest);
	u = normalize(cross(up, w));
	v = normalize(cross(w, u));
}

mat4 Camera::GetProjection() const{
	mat4 proj;

	float n = 0.1f, f = 1000.f;
	proj = perspective(radians(fov), resolution.x / resolution.y, n, f);

	return proj;
}

mat4 Camera::GetView() const{
	float matrix[16];
	mat4 view;

	matrix[0] = u.x; matrix[1] = v.x; matrix[2] = w.x; matrix[3] = 0.f;
	matrix[4] = u.y; matrix[5] = v.y; matrix[6] = w.y; matrix[7] = 0.f;
	matrix[8] = u.z; matrix[9] = v.z; matrix[10] = w.z; matrix[11] = 0.f;
	matrix[12] = -dot(u, position); matrix[13] = -dot(v, position); matrix[14] = -dot(w, position); matrix[15] = 1.f;

	memcpy(&view[0], matrix, 16 * sizeof(float));

	return view;
}