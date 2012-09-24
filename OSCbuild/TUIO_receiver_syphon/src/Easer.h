/*
 *  Easer.h
 *  moviePlayer2_withTUIO
 *
 *  Created by mackey DDA pratt on 3/31/12.
 *  
 *
 */
#pragma once

#include "ofMain.h"

class Easer {

float	i, xC, yC, dx, dy, dx2, dy2;
float	xOrig, yOrig;
float	xE, yE;
int phase;

public:
	Easer();
	bool		update();
	void		startEasing(float _xO, float _yO, float _xT, float _yT);
	void		startEasing(float _xO, float _xT );
	ofVec2f		easedPoint;
	ofVec2f		getEasedPoint();

};
