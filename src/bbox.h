#ifndef H_BBOX_H
#define H_BBOX_H

#include "common.h"

class BBox{
public:
	vec3 fmin, fmax;

public:
	BBox();
	BBox(vec3& min, vec3& max);

	//set bbox range to [inf, -inf]
	void reset();

	//expand from 2d case
	void expand(const BBox& b);
	void expand(const vec3& v);

	//get centric pos of bbox
	vec3 centric() const;
	//get diagonal of bbox
	vec3 diagonal() const;
	//get max extent
	int getMaxExtent() const;

	float getSurfaceArea() const;
};


#endif