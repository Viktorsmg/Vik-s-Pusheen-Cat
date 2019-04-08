#include "commonMath.h"
#include "defines.h"
#include "ivec2.h"
#include "ivec3.h"
#include "vec2.h"
#include "vec3.h"
#include <cmath>//sqrt, for distance, and fabs
#include <iostream>

#include <cstdlib>//rand

unsigned int properMod(int num, unsigned int mod) {
	if (num < 0) return mod - (-1 - num) % mod - 1;
	return num % mod;
}

double properMod(double num, double mod) {
	if (num < 0) return mod - fmod(-1-num,mod)-1;
	return fmod(num, mod);
}

int modItvl(int min, int max, int val) {
	if (val < min) { val = max - (min + properMod(val, max - min + 1)); } else {
		if (val > max) {
			val = min + properMod(val, max - min + 1);
		}
	}
	return val;
}

double modItvl(double min, double max, double val) {
	if (val < min) { val = max - (min + properMod(val, max - min + 1)); } else {
		if (val > max) {
			val = min + properMod(val, max - min + 1);
		}
	}
	return val;
}

//Define this if you want no color bleeding. fcivec will use less memory and processing power then.
#ifndef NOBLEED

//Color bleed strength for fcivec.
//It is advised to keep bleed under 0.5.
const double BLEED = 0.2; 

// <Float Color to Int VECtor>
// Converts a float color (the proper kind of color!) to an int one [0...255], also bleeding channels that are too bright into the rest.
// The bleed strength is configurable.
// Are things slow? Try defining NOBLEED.
ivec3 fcivec(const double &r, const double &g, const double &b) {

	double radd = 0.0, badd = 0.0, gadd = 0.0;
	if (b > 1.0) {
		radd += (b - 1.0) * BLEED;
		gadd += (b - 1.0) * BLEED;
	}
	if (g > 1.0) {
		radd += (g - 1.0) * BLEED;
		badd += (g - 1.0) * BLEED;
	}
	if (r > 1.0) {
		badd += (r - 1.0) * BLEED;
		gadd += (r - 1.0) * BLEED;
	}
	radd += r; badd += b; gadd += g;
	return ivec3(255.0 * clamp(radd, 0.0, 1.0), 255.0 * clamp(gadd, 0.0, 1.0), 255.0 * clamp(badd, 0.0, 1.0));

}

// <Float Color to Int VECtor>
// Converts a float color (the proper kind of color!) to an int one [0...255], also bleeding channels that are too bright into the rest.
// The bleed strength is configurable.
// Are things slow? Try defining NOBLEED.
ivec3 fcivec(const vec3 &col) {

	double radd = 0.0, badd = 0.0, gadd = 0.0;
	if (col.x > 1.0) {
		badd += (col.x - 1.0) * BLEED;
		gadd += (col.x - 1.0) * BLEED;
	}
	if (col.y > 1.0) {
		radd += (col.y - 1.0) * BLEED;
		badd += (col.y - 1.0) * BLEED;
	}
	if (col.z > 1.0) {
		radd += (col.z - 1.0) * BLEED;
		gadd += (col.z - 1.0) * BLEED;
	}
	radd += col.x; gadd += col.y; badd += col.z;
	return ivec3(255.0 * clamp(radd, 0.0, 1.0), 255.0 * clamp(gadd, 0.0, 1.0), 255.0 * clamp(badd, 0.0, 1.0));

}

#else

// <Float Color to Int VECtor>
// Converts a float color (the proper kind of color!) to an int one [0...255].
// This one has no bleeding, and uses less memory and processing power.
ivec3 fcivec(const double &r, const double &g, const double &b) {
	return ivec3(255 * clamp(r, 0.0, 1.0), 255 * clamp(g, 0.0, 1.0), 255 * clamp(b, 0.0, 1.0));

}

// <Float Color to Int VECtor>
// Converts a float color (the proper kind of color!) to an int one [0...255].
// This one has no bleeding, and uses less memory and processing power.
ivec3 fcivec(const vec3 &col) {
	return ivec3(255 * clamp(col.x, 0.0, 1.0), 255 * clamp(col.y, 0.0, 1.0), 255 * clamp(col.z, 0.0, 1.0));
}

#endif

void swap(double &a, double &b) {
	double sw = b;
	b = a; a = sw;
}

void swap(int &a, int &b) {
	int sw = b;
	b = a; a = sw;
}

double dist(double a, double b) {
	return fabs(a - b);
}

double dist(double a) {
	return fabs(a);
}

double dist(const vec2 &a, const vec2 &b) {
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}

double dist(const vec2 &a) {
	return sqrt(a.x*a.x + a.y*a.y);
}

double dist(const vec3 &a,const vec3 &b) {
	double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

double dist(const vec3 &a) {
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

double min(double a, double b) {
	return a > b ? b : a;
}

double max(double a, double b) {
	return a > b ? a : b;
}

double sign(double a, double eps) {
	if (a > (0.0+eps)) return 1.0;
	return a < (0.0 - eps) ? -1.0 : 0.0; 
}

int isign(double a, const double eps) {
	if (a >(0.0 + eps)) return 1;
	return a < (0.0 - eps) ? -1 : 0;
}

double randItvl(double min, double max) {
	return min + (double(rand()) / RAND_MAX)*(max - min);
}

vec2 lerp(const vec2 a, const vec2 b, double lerpFac) {
	return a*lerpFac + b * (1.0 - lerpFac);
}

vec3 lerp(const vec3 a, const vec3 b, double lerpFac) {
	return b * lerpFac + a * (1.0 - lerpFac);
}

double dot(vec2 a, vec2 b) {
	return a.x*b.x + a.y*b.y;
}

double det(vec2 a, vec2 b) { 
	return a.x*b.y - b.x*a.y; 
}

vec2 rotate(vec2 p1, double ang) {
	vec2 polar;
	polar.x = sqrt(p1.x*p1.x + p1.y*p1.y);
	polar.y = atan2(p1.y, p1.x);

	polar.y += ang;
	return vec2(polar.x*cos(polar.y), polar.x*sin(polar.y));
}

vec2 rotate(vec2 origin, vec2 p, double ang) {
	return rotate(p - origin, ang) + origin;
}

bool inBounds(vec2 min, vec2 max, vec2 p) {
	if (min.x > max.x) swap(min.x, max.x);
	if (min.y > max.y) swap(min.y, max.y);
	return p.x>min.x && p.x<max.x && p.y>min.y && p.y<max.y;
}

double heronArea(double a, double b, double c) {
	double p = (a + b + c) / 2.0;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}

//Makes a vector have a length of 1
vec2 normalize(const vec2 &v) {
	double len = dist(v);
	return vec2(v.x / len, v.y / len);
}

vec2 normal(vec2 lp1, vec2 lp2) {
	//1.5708 ~= pi/2
	return normalize(rotate(lp2-lp1, 1.5708));
}