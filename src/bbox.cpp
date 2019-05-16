#include "bbox.h"

BBox::BBox(){
	fmin = { INFINITY, INFINITY, INFINITY };
	fmax = { -INFINITY, -INFINITY, -INFINITY };
}

BBox::BBox(vec3& min, vec3& max){
	fmin = min;
	fmax = max;
}

void BBox::reset(){
	fmin = { INFINITY, INFINITY, INFINITY };
	fmax = { -INFINITY, -INFINITY, -INFINITY };
}

//expand from 2d case
void BBox::expand(const BBox& b){
	fmin.x = fminf(b.fmin.x, fmin.x);
	fmin.y = fminf(b.fmin.y, fmin.y);
	fmin.z = fminf(b.fmin.z, fmin.z);

	fmax.x = fmaxf(b.fmax.x, fmax.x);
	fmax.y = fmaxf(b.fmax.y, fmax.y);
	fmax.z = fmaxf(b.fmax.z, fmax.z);
}

void BBox::expand(const vec3& v){
	fmin.x = fminf(fmin.x, v.x);
	fmin.y = fminf(fmin.y, v.y);
	fmin.z = fminf(fmin.z, v.z);

	fmax.x = fmaxf(fmax.x, v.x);
	fmax.y = fmaxf(fmax.y, v.y);
	fmax.z = fmaxf(fmax.z, v.z);
}

vec3 BBox::centric() const{
	return (fmin + fmax)*0.5f;
}

vec3 BBox::diagonal() const{
	return fmax - fmin;
}

int BBox::getMaxExtent() const{
	vec3 diag = diagonal();
	if (diag.x > diag.y && diag.x > diag.z)
		return 0;
	else if (diag.y > diag.z)
		return 1;
	else
		return 2;
}

float BBox::getSurfaceArea() const{
	vec3 delta = fmax - fmin;
	return 2.f*(delta.x*delta.y + delta.y*delta.z + delta.z*delta.x);
}