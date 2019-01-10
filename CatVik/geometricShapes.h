#pragma once

#include "vec2.h"
#include "vec3.h"
#include <cmath>

//Returns distance to a semicircle's edge at (0;0)
double semiCircle_edge(vec2 uv, double r);

//Returns distance to a filled (with 1.0) circle's edge at (0;0)
double filledCircle_edge(vec2 uv, double r);

//Returns distance to an "edge" (a segment)
double nearEdge(vec2 v1, vec2 v2, vec2 p);

//Returns distance to a triangle's edges at (0;0), except there's only the top part
double triangleTop_edge(vec2 uv, double len);

//Returns distance to a circle at (0;0)
double circleEdge(vec2 pos, double r);

//Returns distance to an ellipse at (0;0)
//Note: This is wrong
//because maths is bad, the formulas for finding said distance are only iterative, IE laggy and complex
//And I'm too lazy to do them
double ellipseEdge(vec2 pos, double r1, double r2);

//Returns whether or not we're in a circle at (0;0)
bool circle(vec2 pos, double r);

bool semiCircle(vec2 pos, double r);
//Returns whether or not we're in an ellipse at (0;0)
//Note: this is legit
bool ellipse(vec2 pos, double r1, double r2);

//Returns whether or not we're in a rectangle
bool rect(vec2 v1, vec2 v2, vec2 p);

bool lineSide(vec2 l1, vec2 l2, vec2 vert);

bool triangle(vec2 l1, vec2 l2, vec2 l3, vec2 vert);

//Returns the distance to a curve defined by a set of points.
double nearCurve(vec2 uv, vec2 curve[], unsigned int curveVerts);

//Returns whether or not a point is in an ngon
//Note: Ngon must be convex
bool point_in_ngon(vec2 points[], unsigned int pointCount, vec2 p);
