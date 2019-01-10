#pragma once
struct ivec2 {
	int x, y;
	ivec2();
	ivec2(int _x, int _y);
	ivec2(int _a);
	//~ivec2();
};

ivec2 operator+(const ivec2 &a, const ivec2 &b);
ivec2 operator-(const ivec2 &a, const ivec2 &b);
ivec2 operator*(const ivec2 &a, const ivec2 &b);
ivec2 operator/(const ivec2 &a, const ivec2 &b);

ivec2 operator+(const ivec2 &a, const int &b);
ivec2 operator-(const ivec2 &a, const int &b);
ivec2 operator*(const ivec2 &a, const int &b);
ivec2 operator/(const ivec2 &a, const int &b);

ivec2 operator+(const int &a, const ivec2 &b);
ivec2 operator-(const int &a, const ivec2 &b);
ivec2 operator*(const int &a, const ivec2 &b);
ivec2 operator/(const int &a, const ivec2 &b);

