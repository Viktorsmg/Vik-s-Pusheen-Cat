#include "ivec2.h"

ivec2::ivec2() { x = 0; y = 0; }
ivec2::ivec2(int _x, int _y) { x = _x; y = _y; }
ivec2::ivec2(int _a) { x = _a; y = _a; }

ivec2 operator+(const ivec2 &a, const ivec2 &b) { return ivec2(a.x + b.x, a.y + b.y); }
ivec2 operator-(const ivec2 &a, const ivec2 &b) { return ivec2(a.x - b.x, a.y - b.y); }
ivec2 operator*(const ivec2 &a, const ivec2 &b) { return ivec2(a.x * b.x, a.y * b.y); }
ivec2 operator/(const ivec2 &a, const ivec2 &b) { return ivec2(a.x / b.x, a.y / b.y); }

ivec2 operator+(const ivec2 &a, const int &b) { return ivec2(a.x + b, a.y + b); }
ivec2 operator-(const ivec2 &a, const int &b) { return ivec2(a.x - b, a.y - b); }
ivec2 operator*(const ivec2 &a, const int &b) { return ivec2(a.x * b, a.y * b); }
ivec2 operator/(const ivec2 &a, const int &b) { return ivec2(a.x / b, a.y / b); }

ivec2 operator+(const int &a, const ivec2 &b) { return ivec2(a + b.x, a + b.y); }
ivec2 operator-(const int &a, const ivec2 &b) { return ivec2(a - b.x, a - b.y); }
ivec2 operator*(const int &a, const ivec2 &b) { return ivec2(a * b.x, a * b.y); }
ivec2 operator/(const int &a, const ivec2 &b) { return ivec2(a / b.x, a / b.y); }