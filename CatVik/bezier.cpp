#include "bezier.h"
#include "vec2.h"
#include "commonMath.h"
#include "lineFunc.h"
#include "geometricShapes.h"
#include <cstdio>

vec2 bezier_point(vec2 p1, vec2 p2, vec2 control, double fac) {
	//TRIanglePoint1/2
	vec2 trip1 = lerp(p1, control, fac);
	vec2 trip2 = lerp(control, p2, fac);

	return lerp(trip1,trip2,fac);


	//return intersect(lineFunc(p1, trip2), lineFunc(p2, trip1));
	//Valid and also makes a bezier, but not as defined (result is slightly squished)
}

vec2 bezier_point_cubic(vec2 p1, vec2 p2, vec2 control1, vec2 control2, double fac) {
	vec2 rectp1 = lerp(p1, control1, fac);
	vec2 rectp2 = lerp(control1, control2, fac);
	vec2 rectp3 = lerp(control2, p2, fac);

	vec2 trip1 = lerp(rectp1, rectp2, fac);
	vec2 trip2 = lerp(rectp2, rectp3, fac);

	return lerp(trip1,trip2,fac);
}

void bezier_curveVerts(vec2 p1, vec2 p2, vec2 control, unsigned short precision, vec2 points[]) {
	for (int i = 0; i < precision; i++) {
		points[i] = bezier_point(p1, p2, control, double(i + 1) / (precision + 1));
	}
}

void bezier_curveVerts_cubic(vec2 p1, vec2 p2, vec2 control1, vec2 control2, unsigned short precision, vec2 points[]) {
	for (int i = 0; i < precision; i++) {
		points[i] = bezier_point_cubic(p1, p2, control1, control2, double(i + 1) / (precision + 1));
	}
}

bool inBezier(vec2 p1, vec2 p2, vec2 control, vec2 uv, unsigned short precision) {
	vec2 *points = new vec2[precision + 2];
	points[0] = p1; points[1] = p2;
	for (int i = 0; i < precision; i++) {
		points[i + 2] = bezier_point(p1, p2, control, double(i+1) / (precision+1));
	}
	bool res = point_in_ngon(points, precision + 2, uv);

	delete[] points;
	return res;
}

bool inCubicBezier(vec2 p1, vec2 p2, vec2 control1, vec2 control2, vec2 uv, unsigned short precision) {
	vec2 *points = new vec2[precision + 2];
	points[0] = p1; points[1] = p2;
	for (int i = 0; i < precision; i++) {
		points[i + 2] = bezier_point_cubic(p1, p2, control1, control2, double(i + 1) / (precision + 1));
	}
	bool res = point_in_ngon(points, precision + 2, uv);

	delete[] points;
	return res;
}

bool inDoubleBezier(vec2 b1_p1, vec2 b1_p2, vec2 b1_control,
					vec2 b2_p1, vec2 b2_p2, vec2 b2_control,
					vec2 uv, unsigned short precision) {
	
	bool inBez1 = inBezier(b1_p1, b1_p2, b1_control, uv, precision);
	bool inBez2 = inBezier(b2_p1, b2_p2, b2_control, uv, precision);
	vec2 rectInitPoints[4] = { b1_p1,b1_p2,b2_p2,b2_p1 };
	bool inRect = point_in_ngon(rectInitPoints, 4, uv);

	//  != is bool XOR
	//Basically: We're in the rect and neither of the beziers, in the first and not in the rect, or in the second and not in the rect
	return (inRect && (inBez1!=inRect && inBez2!=inRect)) || (inBez1&&(inBez1!=inRect)) || (inBez2 && (inBez2 != inRect));
}

bool inDoubleBezier_subSample(vec2 b1_p1, vec2 b1_p2, vec2 b1_control,
					vec2 b2_p1, vec2 b2_p2, vec2 b2_control,
					vec2 uv, unsigned short precision) {
	
	return	inDoubleBezier(b1_p1, b1_p2, b1_control, b2_p1, b2_p2, b2_control, uv + vec2(0.0,0.00001),precision) &&
			inDoubleBezier(b1_p1, b1_p2, b1_control, b2_p1, b2_p2, b2_control, uv + vec2(0.0, -0.00001), precision) && 
			inDoubleBezier(b1_p1, b1_p2, b1_control, b2_p1, b2_p2, b2_control, uv + vec2(0.00001, 0), precision) &&
			inDoubleBezier(b1_p1, b1_p2, b1_control, b2_p1, b2_p2, b2_control, uv + vec2(-0.00001, 0), precision) &&
			inDoubleBezier(b1_p1, b1_p2, b1_control, b2_p1, b2_p2, b2_control, uv + vec2(0.0, 0.0), precision);
}

double nearBezier(vec2 p1, vec2 p2, vec2 control, vec2 uv, unsigned short precision) {
	//At least 2 points always added - the start and end points.
	vec2 *points = new vec2[precision + 2];
	points[0] = p1; points[1] = p2;
	for (int i = 0; i < precision; i++) {
		points[i + 2] = bezier_point(p1, p2, control, double(i + 1) / (precision + 1));
	}
	double minDist=nearEdge(points[1],points[2],uv);
	//We do not want a line connecting the first and last points...
	//We also already got the first line. So we start at 2.
	for (int i = 2; i < (precision + 1); i++) {
		minDist = min(nearEdge(points[i], points[i + 1], uv), minDist);
	}
	//We do want this one thing here, though.
	minDist = min(nearEdge(points[precision+1], points[0], uv), minDist);

	delete[] points;
	return minDist;
}

double nearCubicBezier(vec2 p1, vec2 p2, vec2 control1, vec2 control2, vec2 uv, unsigned short precision) {
	//At least 2 points always added - the start and end points.
	vec2 *points = new vec2[precision + 2];
	points[0] = p1; points[1] = p2;
	for (int i = 0; i < precision; i++) {
		points[i + 2] = bezier_point_cubic(p1, p2, control1, control2, double(i + 1) / (precision + 1));
	}
	double minDist = nearEdge(points[1], points[2], uv);
	//We do not want a line connecting the first and last points...
	//We also already got the first line. So we start at 2.
	for (int i = 2; i < (precision + 1); i++) {
		minDist = min(nearEdge(points[i], points[i + 1], uv), minDist);
	}
	//We do want this one thing here, though.
	minDist = min(nearEdge(points[precision + 1], points[0], uv), minDist);

	delete[] points;
	return minDist;
}

double nearDoubleBezier(vec2 b1_p1, vec2 b1_p2, vec2 b1_control,
						vec2 b2_p1, vec2 b2_p2, vec2 b2_control,
						vec2 uv, unsigned short precision) {

	if (inDoubleBezier_subSample(b1_p1, b1_p2, b1_control, b2_p1, b2_p2, b2_control, uv, precision)) return 0;

	double res=min(nearBezier(b1_p1,b1_p2,b1_control,uv,precision),nearBezier(b2_p1,b2_p2,b2_control,uv,precision));
	res = min(res, min(nearEdge(b1_p1, b2_p1,uv), nearEdge(b1_p2, b2_p2,uv)));
	return res;
}