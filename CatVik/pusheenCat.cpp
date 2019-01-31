#include "pusheenCat.h"

#include "vec2.h"
#include "vec3.h"

#include <cstdlib>//rand()

#include "geometricShapes.h" //We make our fat cat out of geometric shapes
#include "bezier.h"//And bezier curves, those are sweet

#include "commonMath.h" //clamp

#include "lineFunc.h"

#include "mippedTexture.h"
#include <thread>



/*
tailType:
basic,
threeStripes


eyebrowType:
none,
indifferent,
evil,
moe


mouthType:
basic,
O,
OwO


Cat type flags: 
retarded, OwO

*/

catSampleData::catSampleData() {
	fill = 0.0; tailFill = 0.0; edge = 0.0; eye = 0.0;
}

catSampleData::catSampleData(double _fill, double _tailFill, double _edge, double _eye) {
	fill = _fill; tailFill = _tailFill; edge = _edge; eye = _eye;
}

catSampleData mixSampleData(const catSampleData &a, const catSampleData &b) {
	catSampleData res;
	res.fill = a.fill + b.fill;
	res.tailFill = a.tailFill + b.tailFill;
	res.edge = max(a.edge, b.edge);
	res.eye = max(a.eye, b.eye);
	return res;
}

pusheenCat::pusheenCat() {
	retarded = false;
	OwO = false;

	genericDist = 5.0;
	eyeDistMod = 0.0;
	
	eyeSize = 0.8;
	footSize = 0.5;
	footCount = 4;

	frontFat = 0.2;
	backFat = 1.5;
	backInset = 0.1;
	backCircleR = 1.4;
	
	height = 14.0;
	length = 20.0;

	whiskerCount = 3;
	whiskerLen = 3.0;
	tailLen = 4.0;
	tailSize = 1.0;
	earSize = 1.0;

	tailType = stripesTail;

	brow = noBrow;

	mouth = basicMouth;

	borderThickness = 0.1;

	borderColor = vec3(0.8, 0.8, 0.6);
	eyeColor = vec3(0.15, 0.15, 0.15);
	tailColor = vec3(0.2, 0.2, 0.15);
	furColor = vec3(0.3, 0.2, 0.15);

	whiskerAng= 0.4;
	whiskerFakeOccl = 0.5;

	uvoffset = 0.0;
	uvscale = 1.0;

	updateCat();
}

void pusheenCat::randomizePusheen() {
	retarded = !(rand() % 7); // 1/7 chance for a retarded cat
	OwO = !(rand() % 7);// 1/7 chance for a cat with an OwO face
	if (retarded) {
		eyeDistMod = randItvl(-1.0, 1.0);
	} else {
		eyeDistMod = 0.0;
	}
	genericDist = 7.0;
	eyeSize = randItvl(0.3, 1.8);
	footSize = randItvl(0.3, 1.0);
	int amputations = rand() % 40; // 1 in 8 chance of amputations, 5 possibilities
	switch (amputations) {
		case 0: footCount = 3; break;//2x as likely to have just one leg missing
		case 1: footCount = 3; break;
		case 2: footCount = 2; break;
		case 3: footCount = 1; break;
		case 4: footCount = 0; break;
		default: footCount = 4;
	}
	frontFat = randItvl(0.1, 0.8);

	updateCat();
}

void pusheenCat::updateCat() {
	updateFeet();
	updateFront();
	updateBack();
	updateTop();

	updateFace();
	updateWhiskers();
	
	updateTail();
}

vec3 pusheenCat::getCatColor(catSampleData dat) const{
	//Time to mix!
	vec3 resultColor = 0.0;
	//If we're inside the cat, mix with the fill (fur) color, otherwise mix with black.
	if (dat.fill > 0.5) {
		resultColor = borderColor * clamp(dat.edge, 0.0, 1.0) + furColor * clamp(1.0 - dat.edge, 0.0, 1.0);
	} else {
		resultColor = clamp(dat.edge, 0.0, 1.0) * borderColor;
	}
	resultColor = lerp(tailColor, resultColor, clamp(1.0 - dat.tailFill + dat.edge, 0.0, 1.0));
	resultColor = lerp(eyeColor, resultColor, clamp(1.0 - dat.eye, 0.0, 1.0));
	//The eyes will be drawn over the tail stripes... If they ever need to be.
	return resultColor;
}


void pusheenCat::updateFeet() {
	footDist = length / (footCount - 1);
}
catSampleData pusheenCat::getFeet(vec2 uv) const {
	double fill = 0.0, edge = 0.0;
	//Add the feet's borders
	for (int i = 0; i < footCount; i++) {
		edge = max(1.0 - semiCircle_edge(uv + vec2(i*footDist, 0.0), footSize) / borderThickness, edge);
	}
	//Add the feet's fill
	for (int i = 0; i < footCount; i++) {
		fill += semiCircle(uv + vec2(i*footDist, 0.0), footSize);
	}
	//Add the feet connecting lines
	for (int i = 0; i < (footCount - 1); i++) {
		edge = max(1.0 - nearEdge(vec2(i*footDist + footSize, 0.0), vec2((i + 1)*footDist - footSize, 0.0), uv*(-1.0)) / borderThickness, edge);
	}

	return catSampleData(fill, 0.0, edge, 0.0);
}


void pusheenCat::updateFront() {
	front_top = vec2(length + 2 * footSize, height);
	front_bot = vec2(length + 1 * footSize, 0.0);
	//Cat normal is used to "inflate" the cat's front
	frontFat_normal = normal(front_top, front_bot);
	frontControl = lerp(front_top, front_bot, 0.5) + frontFat_normal * frontFat*16.0;
}
catSampleData pusheenCat::getFront(vec2 uv) const {
	double fill = 0.0, edge = 0.0;

	edge = max(1.0 - nearBezier(front_top, front_bot, frontControl, uv*vec2(-1.0, 1.0), 32) / borderThickness, edge);
	fill += inBezier(front_top, front_bot, frontControl, uv*vec2(-1.0, 1.0), 32);

	return catSampleData(fill, 0.0, edge, 0.0);
}

void pusheenCat::updateBack() {
	back_top = vec2(length*backInset, height); 
	back_bot = vec2(-footSize, 0.0);
	
	cat_inside_quad[0] = front_bot; cat_inside_quad[1] = front_top;
	cat_inside_quad[2] = back_top; cat_inside_quad[3] = back_bot;

	baseEarDist = dist(earR[0], earL[2]);

	backFat_normal = normal(back_bot, back_top);
	backControl = lerp(back_top, back_bot, 0.5) + backFat_normal * backFat * vec2(4.0, 8.0);
}
catSampleData pusheenCat::getBack(vec2 uv) const {
	double fill = 0.0, tailFill = 0.0, edge = 0.0, eye = 0.0;

	fill += point_in_ngon(cat_inside_quad, 4, uv*vec2(-1.0, 1.0));
	//Add the edge connecting the 2 ears
	edge = max(1.0 - nearEdge(earR[0], earL[2], uv*vec2(-1.0, 1.0)) / borderThickness, edge);
	//Add the circles between the ears.
	for (int i = 0; i < 3; i++) {
		if (fill>0.5)
			edge = max(1.0 - circleEdge(uv*vec2(1.0, -1.0) + earR[0] + vec2(baseEarDist*i*0.3 + baseEarDist * 0.2, 0.0), baseEarDist*0.1) / borderThickness, edge);
	}

	//Repeat front fat steps for the cat's ass.
	//Start the bezier control point at the centre of the line, and move it forward to determine how fat the cat is...
	edge = max(1.0 - nearBezier(back_top, back_bot, backControl, uv*vec2(-1.0, 1.0), 32) / borderThickness, edge);
	fill += inBezier(back_top, back_bot, backControl, uv*vec2(-1.0, 1.0), 32);

	//Add the edge connecting the ass and the right ear
	edge = max(1.0 - nearEdge(earR[2], back_top, uv*vec2(-1.0, 1.0)) / borderThickness, edge);

	//Add the circle exactly on the butt's top vertex, and the one to its side
	//Remember: no outside                                                                                                                                                      no russian
	//AKA fill>0.5
	if (fill>0.5) {
		edge = max(1.0 - circleEdge(uv*vec2(1.0, -1.0) + back_top, backCircleR) / borderThickness, edge);
		edge = max(1.0 - circleEdge(uv*vec2(1.0, -1.0) + back_top + vec2(3 * backCircleR, 0.0), backCircleR) / borderThickness, edge);
	}

	return catSampleData(fill, tailFill, edge, eye);
}


void pusheenCat::updateTop() {
	earL[0] = front_top;
	earL[1] = front_top - vec2(earSize, -earSize);
	earL[2] = front_top - vec2(2 * earSize, 0.0);

	earR[0] = earL[0] - vec2(genericDist + 2 * earSize, 0.0);
	earR[1] = earL[1] - vec2(genericDist + 2 * earSize, 0.0);
	earR[2] = earL[2] - vec2(genericDist + 2 * earSize, 0.0);
};
catSampleData pusheenCat::getTop(vec2 uv) const {
	double fill = 0.0, tailFill = 0.0, edge = 0.0, eye = 0.0;

	edge = max(1.0 - nearEdge(earL[0], earL[1], uv*vec2(-1.0, 1.0)) / borderThickness, edge);
	edge = max(1.0 - nearEdge(earL[1], earL[2], uv*vec2(-1.0, 1.0)) / borderThickness, edge);

	fill += point_in_ngon(earL, 3, uv*vec2(-1.0, 1.0));

	//We then "shift" this right ear leftwards, turning into... The left ear.
	

	//Bug: weird pattern on ear segments. Seems to occur exactly only when earSize is in [1.0;2.0] ???
	//Bonus debugging: Also happens depending on position. If ears are moved away enough, then it doesn't happen either.
	//WTF?
	//Bug fixed. Fix: additional conversion to double inside bakeSection_obj<t>, line ~18 of textureBaking.h.
	//Remove the double casting thing to see the interesting bug... :O
	//I'll leave these comments here, since this seems worth noting.
	edge = max(1.0 - nearEdge(earR[0], earR[1], uv*vec2(-1.0, 1.0)) / borderThickness, edge);
	edge = max(1.0 - nearEdge(earR[1], earR[2], uv*vec2(-1.0, 1.0)) / borderThickness, edge);
	fill += point_in_ngon(earR, 3, uv*vec2(-1.0, 1.0));

	return catSampleData(fill, tailFill, edge, eye);
}

void pusheenCat::updateTail() {
	//Add variable for                                      \/ this \/
	tailBot = bezier_point(back_bot, back_top, backControl, 1.0 - 0.5);
	tailTop = bezier_point(back_bot, back_top, backControl, 1.0 - 0.6);

	//Used for determining the tail's length/tip
	tailNormal = normal(tailBot, tailTop);
	tailBaseMid = lerp(tailBot, tailTop, 0.5);
	tailTip = tailBaseMid + tailNormal * tailLen;

	//First, we need control points that are on the same line as the tail tip point.
	//For a cubic bezier, this would ensure that the tail has a smooth tip.
	tailTipControlB = normalize(tailBot - tailBaseMid) * tailSize + tailTip;
	tailTipControlT = normalize(tailTop - tailBaseMid) * tailSize + tailTip;

	tailBaseControlB = tailBot + tailNormal * (tailLen / 2.0) + normalize(tailBot - tailBaseMid) * tailSize;
	tailBaseControlT = tailTop + tailNormal * (tailLen / 2.0) + normalize(tailTop - tailBaseMid) * tailSize;

	tailTri[0] = tailTop; tailTri[1] = tailBot; tailTri[2] = tailTip;
}
catSampleData pusheenCat::getTail(vec2 uv) const {
	double fill = 0.0, tailFill = 0.0, edge = 0.0, eye = 0.0;

	edge = max(1.0 - nearCubicBezier(tailBot, tailTip, tailBaseControlB, tailTipControlB, uv*vec2(-1.0, 1.0), 32) / borderThickness, edge);
	edge = max(1.0 - nearCubicBezier(tailTop, tailTip, tailBaseControlT, tailTipControlT, uv*vec2(-1.0, 1.0), 32) / borderThickness, edge);

	//This produces a area with a triangle missing because we do our beziers correctly.
	//We'll have to add the triangle back.
	tailFill += inCubicBezier(tailBot, tailTip, tailBaseControlB, tailTipControlB, uv*vec2(-1.0, 1.0), 32);
	tailFill += inCubicBezier(tailTop, tailTip, tailBaseControlT, tailTipControlT, uv*vec2(-1.0, 1.0), 32);
	tailFill += point_in_ngon(tailTri, 3, uv*vec2(-1.0, 1.0));

	if (fill > 0.5) tailFill = 0;


	//The most difficult part of the cat... The tail stripes.
	//This is a second way of making the stripes: by generating points that lie on the tail's edges,
	//and creating beziers using them.
	//This might leave gaps inbetween the stripes and tail border, but I didn't manage to see them, so that's that.
	///TODO: variable number of tail stripes
	if (tailFill > 0.5) {

		//tailStripe[bezier]#Npoint#N;   tailStripe[bezier]#NControl
		vec2 tS1p1, tS1p2, tS2p1, tS2p2, tS1control, tS2control;
		for (int i = 1; i < 4; i++) {
			tS1p1 = bezier_point_cubic(tailBot, tailTip, tailBaseControlB, tailTipControlB, i*0.25 + 0.075);
			tS1p2 = bezier_point_cubic(tailTop, tailTip, tailBaseControlT, tailTipControlT, i*0.25 + 0.075);
			tS1control = lerp(tS1p1, tS1p2, 0.5) + tailNormal * 0.2;

			tS2p1 = bezier_point_cubic(tailBot, tailTip, tailBaseControlB, tailTipControlB, i*0.25 + 0.175);
			tS2p2 = bezier_point_cubic(tailTop, tailTip, tailBaseControlT, tailTipControlT, i*0.25 + 0.175);
			tS2control = lerp(tS2p1, tS2p2, 0.5) + tailNormal * 0.2;

			edge = max(1.0 - nearDoubleBezier(
				tS1p1, tS1p2, tS1control,
				tS2p1, tS2p2, tS2control,
				uv*vec2(-1.0, 1.0), 20
			) / borderThickness, edge);
		}
	}
	return catSampleData(fill, tailFill, edge, eye);
}

void pusheenCat::updateFace() {
	eyeL = vec2(length*0.7, height*0.8);
	noseTip = eyeL + vec2(genericDist*0.5, 0.0);
	noseL = eyeL + vec2(genericDist*0.3, 0.0 - height * 0.1);
	noseR = eyeL + vec2(genericDist*0.7, 0.0 - height * 0.1);
	noseMid = eyeL + vec2(genericDist*0.5, 0.0 - height * 0.1);
}
catSampleData pusheenCat::getFace(vec2 uv) const {
	double fill = 0.0, tailFill = 0.0, edge = 0.0, eye = 0.0;

	eye = max(1.0 - filledCircle_edge(uv*vec2(-1.0, 1.0) - eyeL, eyeSize) / borderThickness, eye);
	eye = max(1.0 - filledCircle_edge(uv*vec2(-1.0, 1.0) - eyeL - vec2(genericDist, 0.0), eyeSize) / borderThickness, eye);

	edge = max(1.0 - nearCubicBezier(noseL, noseTip, noseMid, noseMid, uv*vec2(-1.0, 1.0), 20) / borderThickness, edge);
	edge = max(1.0 - nearCubicBezier(noseR, noseTip, noseMid, noseMid, uv*vec2(-1.0, 1.0), 20) / borderThickness, edge);

	return catSampleData(fill, tailFill, edge, eye);
}

void pusheenCat::updateWhiskers() {
	whiskerCentreL = eyeL;
	whiskerCentreR = eyeL + vec2(genericDist, 0.0);
}
catSampleData pusheenCat::getWhiskers(vec2 uv, double old_fill) const {
	double fill = old_fill, tailFill = 0.0, edge = 0.0, eye = 0.0;

	//First batch of whiskers, left side: these are "on top" of the cat. They have fake occlusion, accomplished with lerp.
	vec2 whiskerEnd = whiskerCentreL - vec2(2.0*whiskerLen, 0.0);
	whiskerEnd = rotate(whiskerCentreL, whiskerEnd, whiskerAng);
	for (int i = 0; i < whiskerCount; i++) {
		edge = max(1.0 - nearEdge(whiskerEnd, lerp(whiskerCentreL, whiskerEnd, whiskerFakeOccl), uv*vec2(-1.0, 1.0)) / borderThickness, edge);
		whiskerEnd = rotate(whiskerCentreL, whiskerEnd, (whiskerAng * -2.0) / (whiskerCount - 1));
	}


	//Second batch of whiskers, right side: these have real occlusion, they must be "outside" the cat.
	if (fill < 0.5) {
		vec2 whiskerEnd = whiskerCentreR + vec2(2.0*whiskerLen, 0.0);
		whiskerEnd = rotate(whiskerCentreR, whiskerEnd, whiskerAng);
		for (int i = 0; i < whiskerCount; i++) {
			edge = max(1.0 - nearEdge(whiskerEnd, whiskerCentreR, uv*vec2(-1.0, 1.0)) / borderThickness, edge);
			whiskerEnd = rotate(whiskerCentreR, whiskerEnd, (whiskerAng * -2.0) / (whiskerCount - 1));
		}
	}
	return catSampleData(fill, tailFill, edge, eye);
}

vec3 pusheenCat::samplePusheen(vec2 uv) const {

	//For some reason, some of the functions have one or more of their coordinates inverted. Or, the function giving the UV coordinates has them inverted.
	//Either way, there are going to be minuses in places. Lots of minuses in lots of places, starting here.
	uv = uv+vec2(-0.25,-0.5);
	uv = uv*-32.0/uvscale;
	uv = uv + uvoffset * -8.0;
	
	//Fill indicate whether we're inside the cat or not; tailFill - inside the tail. The rest indicate how "close" we are to the respective thing (edge, eye, tail...)
	
	catSampleData res;
	res = mixSampleData(res, getTail(uv));

	res = mixSampleData(res, getFeet(uv));
	res = mixSampleData(res, getFront(uv));
	res = mixSampleData(res, getBack(uv));
	res = mixSampleData(res, getTop(uv));

	res = mixSampleData(res, getFace(uv));
	res = mixSampleData(res, getWhiskers(uv,res.fill));

	return getCatColor(res);
}

//pusheenCat::~pusheenCat() {}

vec3 samplePusheen(double x, double y, const pusheenCat &cat) {
	return cat.samplePusheen(vec2(x, y));
}
