#pragma once
#include "vec2.h"
#include "commonMath.h"

//Returns whether or not a point is in an ngon
//Note: Ngon must be convex
bool point_in_ngon(vec2 points[], unsigned int pointCount, vec2 p);


/*
Returns a bezier curve's point. This one is homegrown!
Note: fac is reversed, and takes arguments from 0 to 1!
*/
vec2 bezier_point(vec2 p1, vec2 p2, vec2 control, double fac);

/*
Returns a bezier curve's point. This one is homegrown!
Note: fac is reversed, and takes arguments from 0 to 1!
*/
vec2 bezier_point_cubic(vec2 p1, vec2 p2, vec2 control1, vec2 control2, double fac);

/*
Creates bezier points/vertices and saves them into a provided array.
*/
void bezier_curveVerts(vec2 p1, vec2 p2, vec2 control, unsigned short precision, vec2 points[]);

/*
Creates cubic bezier points/vertices and saves them into a provided array.
*/
void bezier_curveVerts_cubic(vec2 p1, vec2 p2, vec2 control1, vec2 control2, unsigned short precision, vec2 points[]);



/*
Returns whether the uv point is inside a bezier. 
The shape/ngon defined by the bezier is the curve itself and the line connecting its 2 corners to one another.
It does this by creating an ngon and checking if we're in that.
*/
bool inBezier(vec2 p1, vec2 p2, vec2 control, vec2 uv, unsigned short precision = 12);

/*
Returns whether the uv point is inside a cubic bezier. 
The shape/ngon defined by the bezier is the curve itself and the line connecting its 2 corners to one another.
It does this by creating an ngon and checking if we're in that.
*/
bool inCubicBezier(vec2 p1, vec2 p2, vec2 control1, vec2 control2, vec2 uv, unsigned short precision = 12);


//Returns whether the uv point is inside a double bezier(curved stripe) or not. Can produce artifacts - if it does, use the subSample version!
//inDoubleBezier_subSample
bool inDoubleBezier(vec2 b1_p1, vec2 b1_p2, vec2 b1_control,
					vec2 b2_p1, vec2 b2_p2, vec2 b2_control,
					vec2 uv, unsigned short precision);

//Uses subsampling to improve precision/reduce artifacts of the standard inDoubleBezier function. Literally 5x slower.
//The precision problem is not a problem with the curve precision, but rather float precision.
bool inDoubleBezier_subSample(vec2 b1_p1, vec2 b1_p2, vec2 b1_control,
							  vec2 b2_p1, vec2 b2_p2, vec2 b2_control,
							  vec2 uv, unsigned short precision);


/*
Returns the distance to a bezier curve from the uv point. 
Low precision of the curve can be faster, but also produces spiky artifacts.
*/
double nearBezier(vec2 p1, vec2 p2, vec2 control, vec2 uv, unsigned short precision=12);

/*
Returns the distance to a cubic bezier curve from the uv point.
Low precision of the curve can be faster, but also produces spiky artifacts.
*/
double nearCubicBezier(vec2 p1, vec2 p2, vec2 control1, vec2 control2, vec2 uv, unsigned short precision = 12);


//Returns the distance to a "double bezier" (curved stripe) from the uv point.
//It is possible to be inside the stripe. If so, the distance is 0...
double nearDoubleBezier(vec2 b1_p1, vec2 b1_p2, vec2 b1_control,
						vec2 b2_p1, vec2 b2_p2, vec2 b2_control,
						vec2 uv, unsigned short precision);