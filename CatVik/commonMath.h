#pragma once

#include "ivec2.h"
#include "ivec3.h"
#include "vec2.h"
#include "vec3.h"

//Keeps a value between two others. Useful if things get too bright... Or too dark. 
//No negative colors in practice, though they're fun in theory - check Blender!
template<typename t> 
t clamp(t a, t min, t max) {
	if (a > max) return max;
	if (a < min) return min;
	return a;
}

//Flips a value if it gets out of bounds. Useful for looping menus.
template<typename t> 
t clampF(t a, t min, t max) {
	if (a > max) return min;
	if (a < min) return max;
	return a;
}

//Modulus with proper functionality for negative numbers.
//Normal modulus gives negative and mirrored output for negative numbers.
unsigned int properMod(int num, unsigned int mod);

double properMod(double num, double mod);

//Modulus with an interval instead of a singular value.
int modItvl(int min, int max, int val);

double modItvl(double min, double max, double val);

//Converts 3 float channels to an int color [vector]
//#DEFINE NOBLEED to remove channel bleeding and increase performance
ivec3 fcivec(const double &r, const double &g, const double &b);

//Converts a float color to an int color [vector]
//#DEFINE NOBLEED to remove channel bleeding and increase performance
ivec3 fcivec(const vec3 &col);

void swap(double &a, double &b);
void swap(int &a, int &b);

double dist(double a, double b);

double dist(double a);

double dist(const vec2 &a, const vec2 &b);

double dist(const vec2 &a);

double dist(const vec3 &a, const vec3 &b);

double dist(const vec3 &a);

double min(double a, double b);

double max(double a, double b);

//Returns -1.0 if the sign is -, 0.0 if the number is a 0, and 1.0 if it's a +.
double sign(double a, const double eps = 0.00001);

//Returns a random floating point value in an interval
double randItvl(double min, double max);

//Linear intERPolation
//The interpolation factor mmust be in [0;1]!
//Broken: fac is inverted
//Fix at some point; do note that too many functions use this, correcting the wrong behavior!
vec2 lerp(const vec2 a, const vec2 b, double lerpFac);

//Linear intERPolation
//Not broken!
//Fac should generally be in [0;1]
vec3 lerp(const vec3 a, const vec3 b, double lerpFac);

//Returns the length of the 2 vectors multiplied
double dot(vec2 a, vec2 b);

//Returns the determinant of a 2x2 matrix
double det(vec2 a, vec2 b);

vec2 rotate(vec2 p, double ang);

vec2 rotate(vec2 origin, vec2 p, double ang);

bool inBounds(vec2 min, vec2 max, vec2 p);

double heronArea(double a, double b, double c);

vec2 normalize(const vec2 &v);

//Returns the normal of a line.
//Is normalized itself.
//Those 2 things are *very* different.
vec2 normal(vec2 lp1, vec2 lp2);