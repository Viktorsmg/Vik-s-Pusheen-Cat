#include "geometricShapes.h"

#include "vec2.h"
#include "vec3.h"
#include <cmath>

#include "commonMath.h"//distance
#include "lineFunc.h"//Intersection, perpendicular...

double semiCircle_edge(vec2 uv, double r) {
	if (uv.y>0.0) return 1.0;
	return abs(sqrt(uv.x*uv.x + uv.y*uv.y) - r);
}

double filledCircle_edge(vec2 uv, double r) {
	if ((uv.x*uv.x + uv.y*uv.y)<r*r) return 0.0;
	double res = abs(sqrt(uv.x*uv.x + uv.y*uv.y) - r);
	return res;
}

double nearEdge(vec2 v1, vec2 v2, vec2 p) {
	double a, b, c;//Sides of right angle triangle
	a = dist(p, v1);
	b = dist(p, v2);
	c = dist(v1, v2);

	if((a*a+b*b)<c*c)
	return (heronArea(a,b,c) * 2) / c;

	return min(a, b);
}


double triangleTop_edge(vec2 uv, double len) {
	return max(
			nearEdge(vec2(-len / 2.0, 0.0), vec2(0.0, sqrt(3.0)*len / 2.0), uv),
			nearEdge(vec2( len / 2.0, 0.0), vec2(0.0, sqrt(3.0)*len / 2.0), uv)
			);
}

double circleEdge(vec2 pos, double r) {
	return abs(sqrt(pos.x*pos.x + pos.y*pos.y) - r);
}

double ellipseEdge(vec2 pos, double r1, double r2) {
	return circleEdge(vec2(pos.x*r1, pos.y*r2), r2*r1);
}

bool circle(vec2 pos, double r) {
	return (pos.x*pos.x + pos.y*pos.y)<r*r;
}

bool semiCircle(vec2 pos, double r) {
	if (pos.y > 0.0) return 0.0;
	return (pos.x*pos.x + pos.y*pos.y)<r*r;
}

bool ellipse(vec2 pos, double r1, double r2) {
	return circle(vec2(pos.x*r1, pos.y*r2), r2*r1);
}
 
bool rect(vec2 v1, vec2 v2, vec2 p) {
	double swap;
	if (v1.x>v2.x) { swap = v1.x; v1.x = v2.x; v2.x = swap; }
	if (v1.y>v2.y) { swap = v1.y; v1.y = v2.y; v2.y = swap; }

	return p.x>v1.x && p.x<v2.x && p.y>v1.y && p.y<v2.y;
}

bool lineSide(vec2 l1, vec2 l2, vec2 vert) {
	//Also common formula
	return (vert.x-l1.x)*(l2.y-l1.y)-(vert.y-l1.y)*(l2.x-l1.x)>0.0;
}

bool triangle(vec2 l1, vec2 l2, vec2 l3, vec2 vert) {
	return	(lineSide(l1, l2, l3) == lineSide(l1, l2, vert)) &&
			(lineSide(l2, l3, l1) == lineSide(l2, l3, vert)) &&
			(lineSide(l1, l3, l2) == lineSide(l1, l3, vert));
}

//Finds the function of a perpendicular line, given a target line function and point
//vec2 perpendicular(vec2 lf, vec2 p);

double nearCurve(vec2 uv, vec2 curve[], unsigned int curveVerts) {
	if (curveVerts == 0) return 0;
	if (curveVerts == 1) return dist(uv - curve[0]);
	curveVerts--;
	double res = dist(uv - curve[0]);
	for (int i = 0; i < curveVerts; i++) {
		res = min(res, nearEdge(curve[0], curve[1]));
	}
	return res;
}

bool point_in_ngon(vec2 points[], unsigned int pointCount, vec2 p) {

	int inNgon = 0;
	for (int i = 0; i < (pointCount - 1); i++) {
		inNgon += lineSide(points[i], points[i + 1], p);
	}
	inNgon += lineSide(points[pointCount - 1], points[0], p);
	//Either we're below all lines, or above them.
	//printf("InNgon: %d\n", inNgon);
	return inNgon == pointCount || inNgon == 0;

}