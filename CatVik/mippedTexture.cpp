#include "mippedTexture.h"

#include <iostream> //cout
#include "commonMath.h" //clamp, for limiting textures to the border
#include <cmath> //fmod, for repeating textures

#include <thread>//Multithreading optimisations for mipmap generation and/or texture rendering

#include "vec2.h"
#include "vec3.h"
#include "ivec2.h"

/*
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
*/

//Linearly interpolates between 4 values.
//Assuming a uv position between 0 and 1...
//Pixels: top1 is top left, top2 - top right, bot1 - bottom left, ...
//UV's location is its location relative to the pixels' centers.
vec3 linearInterp(vec3 top1, vec3 top2, vec3 bot1, vec3 bot2, vec2 uv) {
	return (top1*(1.0 - uv.x) + top2 * uv.x)*(1.0 - uv.y) + (bot1*(1.0 - uv.x) + bot2 * uv.x)*uv.y;
}

mippedTexture::mippedTexture() {
	wrapType = null; interpType = constant;
	std::cout << "Warning - creating a texture with no parameters!\n";
	LEVELS = -1;
	sizex = 0; sizey = 0;
	pixels = nullptr; mipmaps = nullptr;
}

mippedTexture::mippedTexture(const int &x, const int &y) {
	wrapType = null; interpType = constant;
	std::cout << "Creating texture with no mipmaps...\n";
	LEVELS = 0;
	sizex = x; sizey = y;
	pixels = new double[x*y * 3];
	mipmaps = nullptr;
}

mippedTexture::mippedTexture(const int &x, const int &y, const int &_levels) {
	wrapType = null; interpType = constant;
	if (_levels == 0) { std::cout << "Warning: creating texture with 0 mipmap levels!";  }
	else { std::cout << "Creating texture with " << _levels << " levels...\n"; }
	LEVELS = _levels;
	sizex = x; sizey = y;
	pixels = new double[x*y*3];

	//By definition, mipmaps always use less than 1/3 normal texture memory, as each mipmap is 1/4 the size of the previous one...
	//lim n->8 90deg sum(1/2^2n) = 1/3
	//Refer to this: https://upload.wikimedia.org/wikipedia/commons/e/ed/Mipmap_illustration2.png
	//This could probably be done using a formula that includes the mipmap levels, to conserve memory.
	if (_levels > 0) { mipmaps = new double[x*y]; } else { mipmaps = nullptr; }
}

mippedTexture::~mippedTexture() {
	if (LEVELS >= 0) delete[] pixels;
	if (LEVELS > 0) delete[] mipmaps;
}

ivec2 mippedTexture::getSize() const {
	return ivec2(sizex, sizey);
}
int mippedTexture::getSizeX() const {
	return sizex;
}
int mippedTexture::getSizeY() const {
	return sizey;
}


void generateMipArea(ivec2 asize, double *mipmap, const double *tex) {
	vec3 sum;

	//The position of the top left pixel in tex
	int postop = 0;

	//The position of the bottom left pixel in tex
	int posbot=0;

	for (int i = 0; i < asize.x; i++) {
		for (int j = 0; j < asize.y; j++) {
			postop = i * 6 + j * 6 * asize.x;
			posbot = i * 6 + (j * 6 + 3)*asize.x;
			sum =	vec3(tex[postop + 0], tex[postop + 1], tex[postop + 2])  +  vec3(tex[postop+3 + 0], tex[postop+3 + 1], tex[postop+3 + 2]) +
					vec3(tex[posbot + 0], tex[posbot + 1], tex[posbot + 2])  +  vec3(tex[posbot+3 + 0], tex[posbot+3 + 1], tex[posbot+3 + 2]);
			sum = sum/4.0;

			mipmap[i * 3 + j * 3 * asize.x + 0] = sum.x;
			mipmap[i * 3 + j * 3 * asize.x + 1] = sum.y;
			mipmap[i * 3 + j * 3 * asize.x + 2] = sum.z;
		}
	}
}


void mippedTexture::generateMipmaps() {
	if (LEVELS == 0) return;
	//The mipmap's own size (x, y)
	int mipsizex = sizex / 4, mipsizey = sizey / 4;
	//The accumulated index shift in the mipmap array
	int mipshift=0;
	const int threadCount = std::thread::hardware_concurrency();
	std::thread *threads = new std::thread[threadCount];
	for (int i = 0; i < threadCount; i++) {
		threads[i] = std::thread ( generateMipArea, ivec2(mipsizex, mipsizey/threadCount), mipmaps+(mipsizex*mipsizey*3*i)/threadCount, pixels);
	}

	for (int i = 0; i < threadCount; i++) {
		threads[i].join();
	}

	//Unimplemented...
	for (int i = 0; i < (LEVELS - 1); i++) {

	}

	delete[] threads;

	return;
}


vec3 mippedTexture::sample(vec2 uv) const {

	if (uv.x > 1.0 || uv.y > 1.0 || uv.x < 0.0 || uv.y < 0.0) {
		if (wrapType == null) return vec3(0.0);
		if (wrapType == edge) uv=vec2(clamp(uv.x, 0.0, 1.0), clamp(uv.y, 0.0, 1.0));
		if (wrapType == repeat) uv=vec2(fmod(fabs(uv.x), 1.0), fmod(fabs(uv.y), 1.0));//fmod doesn't work correctly with negatives, giving a "mirrored" result instead
	}

	if (interpType == constant) {
		int directPos = ( int(uv.x*sizex) + int(uv.y*sizey)  * sizex ) * 3;	//It's a "" 2D "" array
		return vec3(pixels[directPos], pixels[directPos+1], pixels[directPos+2]);
	}

	if (interpType == linear) {
		//Subtract half a pixel to get the neighbourhood instead of the pixels in front

		uv = uv - vec2(1.0 / sizex, 1.0 / sizey)/2.0;
		
		if (uv.x > 1.0 || uv.y > 1.0 || uv.x < 0.0 || uv.y < 0.0) {
			if (wrapType == null) return vec3(0.0);
			if (wrapType == edge) uv = vec2(clamp(uv.x, 0.0, 1.0), clamp(uv.y, 0.0, 1.0));
			if (wrapType == repeat) uv = vec2(fmod(fabs(uv.x), 1.0), fmod(fabs(uv.y), 1.0));
		}

		const ivec2 shift[4] = { ivec2(0,0), ivec2(0,1), ivec2(1,0), ivec2(1,1) };
		ivec2 topleft(sizex*uv.x, sizey*uv.y), pixelPos;
		vec3 interpPixels[4];
		for (int i = 0; i < 4; i++) {
			pixelPos = topleft + shift[i];

			if (pixelPos.x >= sizex || pixelPos.y >= sizey || pixelPos.x < 0 || pixelPos.y < 0) {
				if (wrapType == null) {
					interpPixels[i] = vec3(0.0); continue;
				}
				if (wrapType == edge) pixelPos = ivec2(clamp(pixelPos.x, 0, sizex - 1), clamp(pixelPos.y, 0, sizey - 1));
				if (wrapType == repeat) pixelPos = ivec2(pixelPos.x%sizex, pixelPos.y%sizey);
			}

			interpPixels[i] = vec3(
				pixels[pixelPos.x * 3 + pixelPos.y * 3 * sizex + 0],
				pixels[pixelPos.x * 3 + pixelPos.y * 3 * sizex + 1],
				pixels[pixelPos.x * 3 + pixelPos.y * 3 * sizex + 2]
			);
		}
		//uv = uv + vec2(0.5 / sizex, 0.5 / sizey);
		null;
		return linearInterp(
			interpPixels[0],
			interpPixels[2],
			interpPixels[1],
			interpPixels[3],
			vec2(fmod(uv.x*sizex,1.0), fmod(uv.y*sizey,1.0))
		);

	}
		return vec3(0.25);
}

vec3 mippedTexture::sample(vec2 uv, int level) const {
	return vec3(0.25);
}


vec3 mippedTexture::sample(vec2 uv, double level) const {
	int lowerlvl = int(level);
	return sample(uv, lowerlvl)*(level - double(lowerlvl)) + sample(uv, lowerlvl + 1)*(double(level + 1) - lowerlvl);
}

void mippedTexture::setPixel(ivec2 pos, vec3 color) {
	pixels[(pos.x + pos.y*sizex) * 3 + 0] = color.x;
	pixels[(pos.x + pos.y*sizex) * 3 + 1] = color.y;
	pixels[(pos.x + pos.y*sizex) * 3 + 2] = color.z;
}

void mippedTexture::setPixel(unsigned int pos, vec3 color) {
	pixels[pos * 3 + 0] = color.x;
	pixels[pos * 3 + 1] = color.y;
	pixels[pos * 3 + 2] = color.z;
}


vec3 sample(mippedTexture tex, vec2 uv) {
	return tex.sample(uv);
}

vec3 sample(mippedTexture tex, vec2 uv, int level) {
	return tex.sample(uv, level);
}

vec3 sample(mippedTexture tex, vec2 uv, double level) {
	return tex.sample(uv, level);
}



unsigned int mippedTexture::toDirect(ivec2 pos) const {
	return 3 * (pos.x + pos.y*sizey);
}

unsigned int mippedTexture::toDirect(ivec3 pos) const {
	return pos.x + 3 * pos.y + pos.z * 3 * sizey;
}

unsigned int mippedTexture::toDirect(unsigned int x, unsigned int y) const {
	return 3 * (x + y*sizey);
}

unsigned int mippedTexture::toDirect(unsigned int channel, unsigned int x, unsigned int y) const {
	return channel + 3 * x + y * 3 * sizey;
}

/*
vec3 mippedTexture::sampleDirectClamped(ivec2 pos) {
if (pos.x >= sizex || pos.y > sizey || pos.x < 0 || pos.y < 0) {
if (wrapType == null) return vec3(0.0);
if (wrapType == edge) return sampleDirect(ivec2(clamp(pos.x, 0, sizex-1), clamp(pos.y, 0, sizey-1)));
if (wrapType == repeat) return sampleDirect(ivec2(pos.x%sizex, pos.y%sizey));
}

return vec3(0.25);
}
*/
