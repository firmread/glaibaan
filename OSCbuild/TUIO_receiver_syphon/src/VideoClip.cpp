/*
 *  videoClip.cpp
 *  moviePlayer_zaxis_psm
 *
 *  Created by mackey DDA pratt on 3/28/12.
 */

#include "ofMain.h"     //without this the oFfunction calls in here are unrecognized
#include "videoClip.h"

VideoClip::VideoClip(){}

VideoClip::VideoClip(int _x, int _y, int _w, int _h, string _file ,int _total, int _id) {
	
	yOffsetPct = 0.15; //try editing this for crude calibration to match blob with video corner
	
    ID =  _id;
    targetX = thisX = _x;
    targetY = thisY = _y;
	thisZ = _id;		//just to start
	total = _total;		//numofclips
	
    thisW = _w;
    thisH = _h;
	ROT = 0;			//rotation, degrees
	
    thisMovie.loadMovie(_file);  
	thisMovie.play();
	thisMovie.setLoopState(OF_LOOP_NORMAL); //looping for testing, use OF_LOOP_NONE for not
	
    isPlaying = true;
    isSelected = false;
	isVisible = false;		//eventually, all will be hidden unless the related indicia stamp is present
}

//called from TUIO events in testApp -------------------------
void VideoClip::show() {
    isVisible = true;
	//and stop/reset hiding timer
}
void VideoClip::hide() {
	//WIP implement a timer to delay onset of hiding
    //isVisible = false;
}
void VideoClip::setTargetLocPct (float _px, float _py) { //as percentages of entire screen
    isMoving = true;
    targetX = 1280*_px; //this display is 1400x1400 | Aimee 1280x640 
    targetY = (640*_py)-(640*yOffsetPct); //crude calibration
}
void VideoClip::setRotation(float _angradians) { //range is 0.0 to 6.28 radians at 360°
    rotMgr.setRotation(_angradians);
	rotMgr.updateRotation();
}
//------------------------------------------------


//called from a mouseclick
void VideoClip::setTargetLocation (float _xt, float _yt) {
    isMoving = true;
    targetX = _xt; 
    targetY = _yt;
}


//called when selection changes in main by keyReleased handler
void VideoClip::setSelected(bool b) {	
    isSelected = b;
	//move to front if this is selected 
	if (isSelected) {
		thisZ = total+1;
	} else {
		thisZ = ID;
	}
}

//...also from keyReleased handler, only to the selected videoclip...
void VideoClip::setRotation(bool _keyleft, bool _keyright, bool _keyup, bool _keydown) { //will be {keyleft,keyup,keyright,keydown} booleans
    rotMgr.setRotation(_keyleft,_keyright);
	rotMgr.updateRotation();
}

//main method calls... see earlier versions for use of updateState()

void VideoClip::update() {
	if (isVisible) {
		thisMovie.idleMovie();	//required by ofVideoPlayer
		updateLocation();		//has to happen constantly in case video is still moving when another one is selected
	}
}

void VideoClip::draw() {
	if (isVisible) {
		ofPushMatrix();
		
		ofTranslate(thisX, thisY, thisZ);		
		ofRotate(ROT); //not ofDegToRad(ROT)

		ofSetRectMode(OF_RECTMODE_CENTER);
        thisMovie.draw(0,0);
        ofSetRectMode(OF_RECTMODE_CORNER);
		ofPopMatrix();
	}
}


void VideoClip::updateLocation() { //automatic animation move to clicked location
	
	ROT = rotMgr.updateRotation(); 
	
	if (isMoving) {

		float xDiff = (targetX-thisX);
		float yDiff = (targetY-thisY);
		float xShift = xDiff/RATE;
		thisX = thisX + xShift;
		float yShift = yDiff/RATE;
		thisY = thisY + yShift;
		
		if (abs(yDiff+xDiff) < 4.0) { //dont make this too sensitive, it creates an apparent delay
			thisX = targetX; 
			thisY = targetY;

			isMoving = false;
			//cout << "stopped moving" << endl;
		}
    }
    prevX = thisX; 
    prevY = thisY;
}

/* not using but might want for something else during development....................

 bool VideoClip::updateState(bool _over) { //, bool shouldgrab) 
    bool firstTime = false; //true will mean it has done this for the first time (subsequent cycles return false)
    if (_over) {
		if (! isPlaying) {
			//this is an "ENTER" event, only send play command once
			playThisVideo(); 
			isPlaying = true;
			firstTime = true;
		}
    } 
    else {
		if (! _over) {
			if (isPlaying) {
				//this is a "LEAVE" event
				//if (shouldgrab) grab();
				pauseThisVideo();
				isPlaying = false;
				firstTime = true;
			}
		}
    }
    return firstTime;
}

void VideoClip::playThisVideo() {
    thisMovie.play(); 
    //println("play "+ID);
}
void VideoClip::pauseThisVideo() {
    thisMovie.stop();
    //println("paused "+ID);
}
....................................................................................... */

