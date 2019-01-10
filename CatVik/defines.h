#pragma once

//Window sizes
#define WX 1280
#define WY 720


//Channel bleeding - if a color with a too bright channel is to be rendered,
//it will be postprocessed so that the light spills into other channels as well. IE a color of 5.0 red, 0 green and 0 blue,
//which would normally be pure red and indistinguishable from 1.0 red, ---||---, will instead become slightly more washed out - whiter.

//The performance boost gained from disabling this is negligible.
//Seems like the biggest setback is the drawing of many '''points''' at once.

//#define NOBLEED 1