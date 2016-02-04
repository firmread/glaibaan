/*
 *  Rotator.cpp
 *  moviePlayer4_zaxis_psm
 *
 *  Created by mackey DDA pratt on 3/28/12.
 *  
 *  SIMPLY ACCEPTS A VALUE FOR ROTATION AND ANIMATES TOWARD IT
 *  For Testing: each arrow key press adds(-->) or subtracts(<--) 20 degrees to the rotationTarget

 
 */


#include "ofMain.h"     //without this the use of cout is unrecognized
#include "Rotator.h"

Rotator::Rotator() {

	sDELTA = 60.0;				//a divisor. essentially, rate of deceleration
	STOPACCURACY = 1.0;			//degrees "if this close to target, stop animating"
	rotationTarget = 0.0;
	thisAngle = 0;
	isRotating = false;
}

//from keypress for testing
void Rotator::setRotation(bool _leftkey, bool _rightkey) {
	//if (_leftkey) { setRotTarget(rotationTarget-60); }
	//if (_rightkey) { setRotTarget(rotationTarget+60);  } //can go crazy
	
	if (_leftkey) { setRotTarget(thisAngle-60); }
	if (_rightkey) { setRotTarget(thisAngle+60);  }
}

//from TUIO events via testApp
void Rotator::setRotation(float _angradians) {
	setRotTarget(ofRadToDeg(_angradians)); 
}

void Rotator::setRotTarget(float _angdegrees) {

    isRotating = true;
	rotationTarget = _angdegrees;
	//happens constantly cout << "target angle set=" << _angle << endl;
	
	//int dir = (thisAngle<rotationTarget) ? -1:1;
	
	//rotationTarget = ofClamp(rotationTarget,-360,360);
	
}


//called from update...
float Rotator::updateRotation() {
	
	if (isRotating) {
		//cout << "rotationTarget="<< rotationTarget << "thisAngle="<<thisAngle<<endl;
				
		thisAngle = swingTo(rotationTarget,thisAngle);
		
		if (abs(thisAngle-rotationTarget) < STOPACCURACY) { 
			thisAngle = rotationTarget; 
			isRotating = false;
			//cout << "stopped rotating" << endl;
		}		
	}
	return thisAngle;		
}


float Rotator::swingTo (float aRotEnd, float aRotStart) {
	int sign;
	int vNumOfSteps =20; //causes easing since increments decrease as angle approaches target
	
	float rDiff= (aRotEnd-aRotStart);
	
	sign = (rDiff>0) ? 1 : -1 ;
	
	if (abs(rDiff) > 180) { 
		rDiff= 360-abs(rDiff);  //shortest distance
		sign= sign*(-1);		//also swap direction
	} else {
		rDiff= abs(rDiff);
	}
	
	float rotIncr= (rDiff/vNumOfSteps)*sign; //set final value
	
	float newRot=aRotStart;
	
	newRot = newRot + rotIncr; 
	
	if (newRot > 360) { 
		newRot= newRot-360;
	} else {
		if (newRot < 0) { newRot= 360+newRot;}
	}
	
	return newRot;
}

