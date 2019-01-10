#include "lineFunc.h"
#include "vec2.h"
#include <cmath>//is NotANumber ()
#include "commonMath.h" //swap

const double LINEFUNC_EPS = 0.0000001;

lineFunc::lineFunc() {
	a = 1; b = 0;
}

lineFunc::lineFunc(vec2 p1, vec2 p2) {
	a = (p2.y-p1.y)/(p2.x-p1.x);
	//ax+b=y
	//b=-ax+y
	b = -a * p1.x + p1.y;
}

//lineFunc::~lineFunc() {}

//Returns the intersection point of 2 line functions
vec2 intersect(lineFunc f1, lineFunc f2) {
	vec2 res;
	//a1x+b1=y
	//a2x+b2=y
	//a1x+b1-a2x-b2=0
	//x(a1-a2)=(b2-b1)
	//x=(b2-b1)/(a1-a2)
	res.x = (f2.b - f1.b) / (f1.a - f2.a);
	//a1x+b1=y
	res.y = f1.a*res.x + f1.b;
	return res;
}

bool do_intersect(vec2 s1p1, vec2 s1p2, vec2 s2p1, vec2 s2p2) {
	vec2 res = intersect(lineFunc(s1p1, s1p2), lineFunc(s2p1, s2p2));
	//s1p1 has the lower coordinates of the bounding box and s1p2 has the higher ones
	if (s1p1.x > s1p2.x) swap(s1p1.x, s1p2.x);
	if (s1p1.y > s1p2.y) swap(s1p1.y, s1p2.y);

	if (s2p1.x > s2p2.x) swap(s2p1.x, s2p2.x);
	if (s2p1.y > s2p2.y) swap(s2p1.y, s2p2.y);

	return inBounds(s1p1,s1p2,res) && inBounds(s2p1,s2p2,res);
}

bool do_intersect_segLine(vec2 sp1, vec2 sp2, vec2 lp1, vec2 lp2) {
	vec2 res = intersect(lineFunc(sp1, sp2), lineFunc(lp1, lp2));

	//s1p1 has the lower coordinates of the bounding box and s1p2 has the higher ones
	if (sp1.x > sp2.x) swap(sp1.x, sp2.x);
	if (sp1.y > sp2.y) swap(sp1.y, sp2.y);

	return inBounds(sp1,sp2,res);
}

bool do_intersect_segRay(vec2 sp1, vec2 sp2, vec2 rpe, vec2 rpdef) {
	vec2 res = intersect(lineFunc(sp1, sp2), lineFunc(rpe, rpdef));
	//vec2 res = intersect_precise(sp1, sp2, rpe, rpdef);

	if (sp1.x > sp2.x) swap(sp1.x, sp2.x);
	if (sp1.y > sp2.y) swap(sp1.y, sp2.y);

	bool rayDirX = rpe.x < rpdef.x;
	bool rayDirY = rpe.y < rpdef.y;

	bool bounded = inBounds(sp1, sp2, res);
	//res = rpe-res;

	bool resSectorX = res.x < rpe.x;
	bool resSectorY = res.y < rpe.y;

	return ((rayDirX + rayDirY * 2) == (resSectorX + resSectorY * 2)) && bounded;
}

double lineFunc::getx(double y) {
	//ax+b=y
	//ax=y-b
	//x=(y-b)/a
	return (y-b) / a;
}

double lineFunc::gety(double x) {
	//ax+b=y
	return a*x+b;
}

lineFunc perpendicular(lineFunc lf) {
	//Common formula
	lf.a = -1 / lf.a;
	return lf;
}

lineFunc perpendicular(lineFunc lf, vec2 target) {
	lf = perpendicular(lf);
	//ax+b=y
	//b=y-ax
	lf.b = target.y - lf.a*target.x;
	return lf;
}
