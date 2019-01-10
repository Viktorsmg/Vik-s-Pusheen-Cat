#pragma once

//Has defines for important code and very global variables


//Window X size
extern int WX;
//Window Y size
extern int WY;


/*
Channel bleeding - if a color with a too bright channel is to be rendered,
it will be postprocessed so that the light spills into other channels as well. IE a color of 5.0 red, 0 green and 0 blue,
which would normally be pure red and indistinguishable from 1.0 red, ---||---, will instead become slightly more washed out - whiter.

The performance boost gained from disabling this is negligible.
Seems like the biggest setback instead is the drawing of many '''points''' at once and mippedTexture.
*/

//#define NOBLEED 1