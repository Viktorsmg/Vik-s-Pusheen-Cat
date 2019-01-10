#pragma once
struct vec4 {
	double x, y, z, w;
	vec4();
	vec4(const double _x, const double _y, const double _z, const double _w);
	vec4(const double _a);
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