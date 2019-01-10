#pragma once
struct vec2 {
	double x, y;
	vec2();
	vec2(double _x, double _y);
	vec2(double _a);
	//~vec2();
};

vec2 operator+(const vec2 &a, const vec2 &b);
vec2 operator-(const vec2 &a, const vec2 &b);
vec2 operator*(const vec2 &a, const vec2 &b);
vec2 operator/(const vec2 &a, const vec2 &b);

vec2 operator+(const vec2 &a, const double &b);
vec2 operator-(const vec2 &a, const double &b);
vec2 operator*(const vec2 &a, const double &b);
vec2 operator/(const vec2 &a, const double &b);

vec2 operator+(const double &a, const vec2 &b);
vec2 operator-(const double &a, const vec2 &b);
vec2 operator*(const double &a, const vec2 &b);
vec2 operator/(const double &a, const vec2 &b);

vec2 operator-(const vec2 &a);