#pragma once

#include "vec3.h"
#include "vec2.h"

#include "mippedTexture.h"

enum tailType {
	basicTail,
	stripesTail
};

enum eyebrowType {
	noBrow,
	indifferentBrow,
	evilBrow,
	moeBrow
};

enum mouthType {
	basicMouth,
	OMouth,
	OwOMouth
};

class pusheenCat {
public:
	//Is the cat retarded? It's eye distance will be modified.
	bool retarded;

	//Does the cat have an OwO face?
	bool OwO;

	//If the cat is retarded, the distance between its eyes is shorter/longer
	double eyeDistMod;

	//Generic distance for eyes and ears
	double genericDist;

	//Eye size
	double eyeSize;

	//The size of the cat's feet
	double footSize;

	//Is the cat an amputee?
	int footCount;

	//How fat it is from the front
	double frontFat;

	//How fat it is from the back
	double backFat;
	
	//How much inset the butt is relative to the cat's total length
	double backInset;

	//The radius of the back circles; Does not affect ear circles
	double backCircleR;
	
	//How tall the cat is, measured flat part above legs to flat part between ears
	double height;

	//How long the cat is
	//Note: Only affects base foot distance, eye distance, ear distance and eye distance
	double length;

	//Number of whiskers...
	int whiskerCount;

	//Whiskers' length...
	double whiskerLen;

	//How long the tail is
	double tailLen;

	//How large/fluffy/fat the tail is
	double tailSize;

	//How tall&wide the ears are
	double earSize;

	//What type of tail the cat has
	tailType tailType;

	//What type of eyebrows the cat has
	eyebrowType brow;

	//What type of mouth the cat has
	mouthType mouth;

	double borderThickness;
	vec3 borderColor, eyeColor, tailColor, furColor;

	//Angle of the first and last whisker on each side, in radians.
	double whiskerAng;

	//Fake whisker occlusion factor, for the left-side whiskers.
	double whiskerFakeOccl;

	//Render UV offset.
	vec2 uvoffset;
	//Render UV scale.
	vec2 uvscale;

	pusheenCat();
	void randomizePusheen();
	vec3 samplePusheen(vec2 uv) const;
	//~pusheenCat();
};

vec3 samplePusheen(double x, double y, const pusheenCat &cat);