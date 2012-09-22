/*
 *  Rotator.cpp
 *  moviePlayer4_zaxis_psm
 *
 *  Created by mackey DDA pratt on 3/28/12.
 *  
 *  SIMPLY ACCEPTS A VALUE FOR ROTATION AND ANIMATES TOWARD IT
 *  For Testing: each arrow key press adds(-->) or subtracts(<--) 20 degrees to the rotationTarget
 *  see previous versions of Rotator for keypress'd continuous change
 
 *  this algorithm needeth much improvement, should ease-in-out
 *  not using right now
 */


#include "ofMain.h"     //without this the use of cout is unrecognized
#include "Rotator.h"


Rotator::Rotator() {

	sDELTA = 60.0;				//essentially, rate of deceleration
	STOPACCURACY = 10.0;		//"if this close to target, stop animating"
	rotationTarget = 0.0;
	thisAngle = 0;
	isRotating = false;
}
//from TUIO events via testApp
void Rotator::setRotation(float _angradians) {
	setRotTarget(ofRadToDeg(_angradians)); 
}

//from keypress for testing
void Rotator::setRotation(bool _leftkey, bool _rightkey) {
	if (_leftkey) { setRotTarget(rotationTarget-60); }
	if (_rightkey) { setRotTarget(rotationTarget+60);  }
}

void Rotator::setRotTarget(float _angle) {
	//simulates interface for TUIO reporting
	//float rotNow = thisAngle; 
	//float targetRot = _angle;
	//-- easer.startEasing(rotNow,targetRot); --//
	
    isRotating = true;
	rotationTarget = _angle;
	//cout << "target angle set=" << _angle << endl;
}


//called from update...
float Rotator::updateRotation() {
	
		return rotationTarget;
	
	//if (isRotating) {
//		
//		/* -- not debugged yet
//		if (! easer.update()) { 
//			isRotating = false;
//		} else {
//			ofVec2f newpoint = easer.getEasedPoint();
//			thisAngle = newpoint.x;
//		}
//		-- */
//		
//		float aDiff = (rotationTarget-thisAngle);
//		//cout << "abs(aDiff)="<< abs(aDiff) << endl;
//		
//		float aShift = aDiff/sDELTA;
//		thisAngle = thisAngle + aShift;
//				
//		if (abs(aDiff) < STOPACCURACY) { //dont make this too sensitive, it creates an apparent delay
//			thisAngle = rotationTarget; 
//			isRotating = false;
//			cout << "stopped rotating" << endl;
//		}		
//	}
//	return thisAngle;		//apparently do not need to correct for 0-360 range required
	

}

