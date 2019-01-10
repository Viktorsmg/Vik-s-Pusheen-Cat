#include "textureBaking.h"
#include <thread>

void bakeSection(mippedTexture &texture, vec3(*sample)(double, double),
				 const unsigned int secStart, const unsigned int secEnd) {
	for (unsigned i = secStart; i < secEnd; i++) {
		texture.setPixel(i, sample((i%texture.sizex) / double(texture.sizex), (i / texture.sizex) / double(texture.sizey)));
	}
}

void threadedBake(mippedTexture &texture, vec3(*sample)(double, double),
				  const unsigned short threads) {
	unsigned int sectionLen = (texture.sizex*texture.sizey) / threads;
	std::thread *sectionRenderThreads = new std::thread[threads];
	for (int i = 0; i < (threads - 1); i++) {
		sectionRenderThreads[i] = std::thread(bakeSection, std::ref(texture), sample, i*sectionLen, (i + 1)*sectionLen);
	}
	//The last thread's section might be larger due to nondivisible pixel counts
	sectionRenderThreads[threads - 1] = std::thread(bakeSection, std::ref(texture), std::ref(sample), (threads - 1)*sectionLen, texture.sizex*texture.sizey);

	for (int i = 0; i < threads; i++) {
		sectionRenderThreads[i].join();
	}
	delete[] sectionRenderThreads;
}