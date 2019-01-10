#pragma once

#include "vec2.h"

struct lineFunc {
	//ax+b=y
	//a - slope
	//b - vertical offset
	double a, b; 

	lineFunc();
	lineFunc(vec2 p1, vec2 p2);
	//~lineFunc();
	double gety(double x = 0);
	double getx(double y = 0);
};

vec2 intersect(lineFunc f1, lineFunc f2);

bool do_intersect(vec2 s1p1, vec2 s1p2, vec2 s2p1, vec2 s2p2);

bool do_intersect_segLine(vec2 sp1, vec2 sp2, vec2 lp1, vec2 lp2);

//Ray end and another ray-defining point are used, in this order.
bool do_intersect_segRay(vec2 sp1, vec2 sp2, vec2 rpe, vec2 rpdef);

lineFunc perpendicular(lineFunc lf);

lineFunc perpendicular(lineFunc lf, vec2 target);