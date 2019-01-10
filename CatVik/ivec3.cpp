#include "ivec3.h"

ivec3::ivec3() { x = 0; y = 0; z = 0; }
ivec3::ivec3(const int _x, const int _y, const int _z) { x = _x; y = _y; z = _z; }
ivec3::ivec3(const int _a) { x = _a; y = _a; z = _a; }

ivec3 operator+(const ivec3 &a, const ivec3 &b) { return ivec3(a.x + b.x, a.y + b.y, a.z + b.z); }
ivec3 operator-(const ivec3 &a, const ivec3 &b) { return ivec3(a.x - b.x, a.y - b.y, a.z - b.z); }
ivec3 operator*(const ivec3 &a, const ivec3 &b) { return ivec3(a.x * b.x, a.y * b.y, a.z * b.z); }
ivec3 operator/(const ivec3 &a, const ivec3 &b) { return ivec3(a.x / b.x, a.y / b.y, a.z / b.z); }

ivec3 operator+(const ivec3 &a, const int &b) { return ivec3(a.x + b, a.y + b, a.z + b); }
ivec3 operator-(const ivec3 &a, const int &b) { return ivec3(a.x - b, a.y - b, a.z - b); }
ivec3 operator*(const ivec3 &a, const int &b) { return ivec3(a.x * b, a.y * b, a.z * b); }
ivec3 operator/(const ivec3 &a, const int &b) { return ivec3(a.x / b, a.y / b, a.z / b); }

ivec3 operator+(const int &a, const ivec3 &b) { return ivec3(a + b.x, a + b.y, a + b.z); }
ivec3 operator-(const int &a, const ivec3 &b) { return ivec3(a - b.x, a - b.y, a - b.z); }
ivec3 operator*(const int &a, const ivec3 &b) { return ivec3(a * b.x, a * b.y, a * b.z); }
ivec3 operator/(const int &a, const ivec3 &b) { return ivec3(a / b.x, a / b.y, a / b.z); }

ivec3 operator-(const ivec3 &a) { return ivec3(-a.x, -a.y, -a.z); }