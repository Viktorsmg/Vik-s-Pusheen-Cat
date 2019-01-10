#pragma once

#include "ivec2.h"
#include "ivec3.h"
#include "vec2.h"
#include "vec3.h"

enum interp {
	constant,
	linear,
	cubic //Will probably stay unimplemented!
};

enum wrap {
	null,
	edge,
	repeat
};

vec3 linearInterp(vec3 top1, vec3 top2, vec3 bot1, vec3 bot2, vec2 uv);

class mippedTexture {
public:
	//constant, linear, cubic
	interp interpType;
	//null, edge, repeat
	wrap wrapType;
	mippedTexture();
	mippedTexture(const int &x, const int &y);
	mippedTexture(const int &x, const int &y, const int &_levels);
	~mippedTexture();

	unsigned int toDirect(ivec2 pos) const;
	//Note: the first coordinate is the channel.
	unsigned int toDirect(ivec3 pos) const;

	unsigned int toDirect(unsigned int x, unsigned int y) const;
	unsigned int toDirect(unsigned int channel, unsigned int x, unsigned int y) const;

	ivec2 getSize() const;
	int getSizeX() const;
	int getSizeY() const;

	void generateMipmaps();

	vec3 sample(vec2 uv) const;
	vec3 sample(vec2 uv, int level) const;
	vec3 sample(vec2 uv, double level) const;

	//Argument is pixel coordiantes X and Y.
	void setPixel(ivec2 pos, vec3 color);
	//Argument is PIXEL coordinate, not direct channel coordinate!
	void setPixel(unsigned int pos, vec3 color);

	//Mipmaps a specific area, use for multithreading
	//void generateMipArea(ivec2 asize, double *mipmap, const double *tex);
	

	int sizex, sizey;
	int LEVELS;

	//FACT: 1D arrays are SMALLER and FASTER than multidimensional ones.
	double *pixels;
	double *mipmaps;

};

void generateMipArea(ivec2 asize, double *mipmap, const double *tex);

vec3 sample(mippedTexture tex, vec2 uv);
vec3 sample(mippedTexture tex, vec2 uv, int level);
vec3 sample(mippedTexture tex, vec2 uv, double level);
