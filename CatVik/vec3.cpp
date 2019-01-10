#include "vec3.h"

vec3::vec3() { x = 0; y = 0; z = 0; }
vec3::vec3(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }
vec3::vec3(double _a) { x = _a; y = _a; z = _a; }

vec3 operator+(const vec3 &a, const vec3 &b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
vec3 operator-(const vec3 &a, const vec3 &b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
vec3 operator*(const vec3 &a, const vec3 &b) { return vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
vec3 operator/(const vec3 &a, const vec3 &b) { return vec3(a.x / b.x, a.y / b.y, a.z / b.z); }

vec3 operator+(const vec3 &a, const double &b) { return vec3(a.x + b, a.y + b, a.z + b); }
vec3 operator-(const vec3 &a, const double &b) { return vec3(a.x - b, a.y - b, a.z - b); }
vec3 operator*(const vec3 &a, const double &b) { return vec3(a.x * b, a.y * b, a.z * b); }
vec3 operator/(const vec3 &a, const double &b) { return vec3(a.x / b, a.y / b, a.z / b); }

vec3 operator+(const double &a, const vec3 &b) { return vec3(a + b.x, a + b.y, a + b.z); }
vec3 operator-(const double &a, const vec3 &b) { return vec3(a - b.x, a - b.y, a - b.z); }
vec3 operator*(const double &a, const vec3 &b) { return vec3(a * b.x, a * b.y, a * b.z); }
vec3 operator/(const double &a, const vec3 &b) { return vec3(a / b.x, a / b.y, a / b.z); }
