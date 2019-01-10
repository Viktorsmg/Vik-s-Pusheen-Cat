#pragma once
struct vec4 {
	double x, y, z, w;
	vec4();
	vec4(double _x, double _y, double _z, double _w);
	vec4(double _a);
	//~vec4();
};

vec4 operator+(const vec4 &a, const vec4 &b);
vec4 operator-(const vec4 &a, const vec4 &b);
vec4 operator*(const vec4 &a, const vec4 &b);
vec4 operator/(const vec4 &a, const vec4 &b);

vec4 operator+(const vec4 &a, const double &b);
vec4 operator-(const vec4 &a, const double &b);
vec4 operator*(const vec4 &a, const double &b);
vec4 operator/(const vec4 &a, const double &b);

vec4 operator+(const double &a, const vec4 &b);
vec4 operator-(const double &a, const vec4 &b);
vec4 operator*(const double &a, const vec4 &b);
vec4 operator/(const double &a, const vec4 &b);

vec4 operator-(const vec4 &a);