#pragma once
struct vec3 {
	double x, y, z;
	vec3();
	vec3(double _x, double _y, double _z);
	vec3(double _a);
	//~vec3();
};

vec3 operator+(const vec3 &a, const vec3 &b);
vec3 operator-(const vec3 &a, const vec3 &b);
vec3 operator*(const vec3 &a, const vec3 &b);
vec3 operator/(const vec3 &a, const vec3 &b);

vec3 operator+(const vec3 &a, const double &b);
vec3 operator-(const vec3 &a, const double &b);
vec3 operator*(const vec3 &a, const double &b);
vec3 operator/(const vec3 &a, const double &b);

vec3 operator+(const double &a, const vec3 &b);
vec3 operator-(const double &a, const vec3 &b);
vec3 operator*(const double &a, const vec3 &b);
vec3 operator/(const double &a, const vec3 &b);

vec3 operator-(const vec3 &a);