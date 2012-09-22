/*
 *  Easer.cpp
 *  moviePlayer4_zaxis_psm
 *
 *  Created by mackey DDA pratt on 3/31/12.
 *  simplistic ease-in-out for known start&stop points using cosine curve
 *	NOT FULLY DEBUGGED
 */
 
//does NOT have calculation for "faster" move relative to lesser distances...
//...all the moves are the same speed

#include "Easer.h"

Easer::Easer(){};

//for computing x,y...
void Easer::startEasing(float _xO, float _yO, float _xT, float _yT ) {
	xOrig = _xO;
	yOrig = _yO;
	dx = (_xT-_xO);
    dx2 = dx/2.0;
	dy = (_yT-_yO);
    dy2 = dy/2.0;
    phase =0;
    i=0;			//treated as degrees to feed the cos function
}
//for a single value, such as rotation...
void Easer::startEasing(float _xO, float _xT ) {
	xOrig = _xO;
	yOrig = 9999;		//to indicate should be ignored in update() 
	yE = 0;
    dx2 = (_xT-_xO)/2.0;
    dy2 = 9999;
    phase =0;
    i=0;
}

ofVec2f Easer::getEasedPoint() {
	return easedPoint;	//is set in update()
}

bool Easer::update() {
	
    bool isDone=false;
	
    switch (phase) {
			
		case 0:  //ease in
			xC = 1 - cos(ofDegToRad (i));
			xE = (xC*dx2)+xOrig;
			
			if (yOrig != 9999) {
				yC = 1 - cos(ofDegToRad (i));
				yE = (yC*dy2)+yOrig;
			}
			
			easedPoint.set(xE,yE);
			
			i ++;
			if (i>90) phase=1; //at the midpoint now ease out
			break;
			
		case 1:  //ease out
			i --;
			xC = 1- cos(ofDegToRad (i));
			xE = (dx - (xC*dx2))+xOrig;
			
			if (yOrig != 9999) {
				yC = 1- cos(ofDegToRad (i));
				yE = (dy - (yC*dy2))+yOrig; 
			}
			
			easedPoint.set(xE,yE);
			
			if (i<0) phase=2;
			break;
			
		case 2:
			isDone = true;
    }
	cout << "Easer updated" << easedPoint.x << endl;
    return isDone;
}
  