#include "vec4.h"

vec4::vec4() { x = 0; y = 0; z = 0; w = 0; }
vec4::vec4(const double _x, const double _y, const double _z, const double _w) { x = _x; y = _y; z = _z; w = _w; }
vec4::vec4(const double _a) { x = _a; y = _a; z = _a; w = _a; }

vec4 operator+(const vec4 &a, const vec4 &b) { return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
vec4 operator-(const vec4 &a, const vec4 &b) { return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
vec4 operator*(const vec4 &a, const vec4 &b) { return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
vec4 operator/(const vec4 &a, const vec4 &b) { return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }

vec4 operator+(const vec4 &a, const double &b) { return vec4(a.x + b, a.y + b, a.z + b, a.w + b); }
vec4 operator-(const vec4 &a, const double &b) { return vec4(a.x - b, a.y - b, a.z - b, a.w - b); }
vec4 operator*(const vec4 &a, const double &b) { return vec4(a.x * b, a.y * b, a.z * b, a.w * b); }
vec4 operator/(const vec4 &a, const double &b) { return vec4(a.x / b, a.y / b, a.z / b, a.w / b); }

vec4 operator+(const double &a, const vec4 &b) { return vec4(a + b.x, a + b.y, a + b.z, a + b.w); }
vec4 operator-(const double &a, const vec4 &b) { return vec4(a - b.x, a - b.y, a - b.z, a - b.w); }
vec4 operator*(const double &a, const vec4 &b) { return vec4(a * b.x, a * b.y, a * b.z, a * b.w); }
vec4 operator/(const double &a, const vec4 &b) { return vec4(a / b.x, a / b.y, a / b.z, a / b.w); }

vec4 operator-(const vec4 &a) { return vec4(-a.x, -a.y, -a.z, -a.w); }
