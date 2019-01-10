#include "vec2.h"

vec2::vec2() { x = 0; y = 0; }
vec2::vec2(const double _x, const double _y) { x = _x; y = _y; }
vec2::vec2(const double _a) { x = _a; y = _a; }

vec2 operator+(const vec2 &a, const vec2 &b) { return vec2(a.x + b.x, a.y + b.y); }
vec2 operator-(const vec2 &a, const vec2 &b) { return vec2(a.x - b.x, a.y - b.y); }
vec2 operator*(const vec2 &a, const vec2 &b) { return vec2(a.x * b.x, a.y * b.y); }
vec2 operator/(const vec2 &a, const vec2 &b) { return vec2(a.x / b.x, a.y / b.y); }

vec2 operator+(const vec2 &a, const double &b) { return vec2(a.x + b, a.y + b); }
vec2 operator-(const vec2 &a, const double &b) { return vec2(a.x - b, a.y - b); }
vec2 operator*(const vec2 &a, const double &b) { return vec2(a.x * b, a.y * b); }
vec2 operator/(const vec2 &a, const double &b) { return vec2(a.x / b, a.y / b); }

vec2 operator+(const double &a, const vec2 &b) { return vec2(a + b.x, a + b.y); }
vec2 operator-(const double &a, const vec2 &b) { return vec2(a - b.x, a - b.y); }
vec2 operator*(const double &a, const vec2 &b) { return vec2(a * b.x, a * b.y); }
vec2 operator/(const double &a, const vec2 &b) { return vec2(a / b.x, a / b.y); }

vec2 operator-(const vec2 &a) { return vec2(-a.x, -a.y); }