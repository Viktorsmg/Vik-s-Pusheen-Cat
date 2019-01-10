#pragma once
struct ivec3 {
	int x, y, z;
	ivec3();
	ivec3(const int _x, const int _y, const int _z);
	ivec3(const int _a);
	//~ivec3();
};

ivec3 operator+(const ivec3 &a, const ivec3 &b);
ivec3 operator-(const ivec3 &a, const ivec3 &b);
ivec3 operator*(const ivec3 &a, const ivec3 &b);
ivec3 operator/(const ivec3 &a, const ivec3 &b);

ivec3 operator+(const ivec3 &a, const int &b);
ivec3 operator-(const ivec3 &a, const int &b);
ivec3 operator*(const ivec3 &a, const int &b);
ivec3 operator/(const ivec3 &a, const int &b);

ivec3 operator+(const int &a, const ivec3 &b);
ivec3 operator-(const int &a, const ivec3 &b);
ivec3 operator*(const int &a, const ivec3 &b);
ivec3 operator/(const int &a, const ivec3 &b);

ivec3 operator-(const ivec3 &a);