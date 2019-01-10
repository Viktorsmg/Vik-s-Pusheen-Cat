#pragma once
#include "mippedTexture.h"

#include <thread>


void bakeSection(mippedTexture &texture, vec3(*sample)(double, double),
				 const unsigned int secStart, const unsigned int secEnd);

//Renders a section of the texture using a sampling function. Useful for multithreading.
//The sampling function takes an additional sampler object, which it can use to get info from, like what is actually being sampled.
template<typename sampler>
void bakeSection_obj(mippedTexture &texture, vec3(*sample)(double, double, const sampler&),
					 const unsigned int secStart, const unsigned int secEnd, const sampler &SObj) {
	for (unsigned i = secStart; i < secEnd; i++) {
		//                If you remove this, there are very specific almost negligible artifacts with interesting shapes on the default cat's ears... ???
		//                                                                    \/     \/
		texture.setPixel(i, sample((i%texture.sizex) / double(texture.sizex), ((double)i / texture.sizex) / double(texture.sizey), SObj));
	}
}



void threadedBake(mippedTexture &texture, vec3(*sample)(double, double),
				  const unsigned short threads);


template<typename sampler>
void threadedBake(mippedTexture &texture, vec3(*sample)(double, double, const sampler&),
				  const sampler &SObj, const unsigned short threads) {
	unsigned int sectionLen = (texture.sizex*texture.sizey) / threads;
	std::thread *sectionRenderThreads = new std::thread[threads];
	for (int i = 0; i < (threads - 1); i++) {
		sectionRenderThreads[i] = std::thread(
		bakeSection_obj<sampler>, std::ref(texture), sample, i*sectionLen, (i + 1)*sectionLen, SObj);
	}
	//The last thread's section might be larger due to nondivisible pixel counts
	sectionRenderThreads[threads - 1] = std::thread(
		bakeSection_obj<sampler>, std::ref(texture), sample, (threads - 1)*sectionLen, 
		texture.sizex*texture.sizey, SObj);

	for (int i = 0; i < threads; i++) {
		sectionRenderThreads[i].join();
	}
	delete[] sectionRenderThreads;
}
