/*
 *  Scene.cpp
 *  moviePlayer1big_withTUIO
 *
 *  Created by mackey DDA pratt on 4/9/12.
 *
 *
 */

#include "Scene.h"

Scene::Scene(int _x, int _y, int _w, int _h, string _BGfilename, int _total, int _id) {
	
	//NOTICE, _x is sent here already corrected for width of this display & centering of panorama picture
	
	numOfDetails=0; //udates automatically each time initDetail is called from Main (testApp)

	panorama.loadImage(_BGfilename);
	panorama.setAnchorPercent(0.5,0.5); 
	//moves "center" coordinate to center of picture but confuses Detail translations
	
	yOffsetPct = 0.15; //try editing this for crude calibration to align TUIO blob with image
	
	ID =  _id;
    targetX = thisX = _x;
    targetY = thisY = _y;
	thisZ = _id;			//just to start
	total = _total;			//numofscenes
	
    thisW = _w;
    thisH = _h;
	ROT = 0;				//rotation, degrees
	
	isMoving = true;
    isSelected = false;
	isVisible = false;		//eventually, all will be hidden unless the related indicia stamp is present	
}
//called from main during setup()...
void Scene::initDetail(string _videofile, float _x, float _y) { //string _stillfile, 
	Detail d;
	
	d.animation.loadMovie(_videofile);
	d.xoffset = _x;
	d.yoffset = _y;
	
	theDetails.push_back(d); //add new Detail object to theDetails array
	numOfDetails++;
}

//main method calls...

void Scene::setup() {
	for (int i=0; i<numOfDetails; i++) {
		theDetails[i].setup();
	}

}
void Scene::update() {
	if (isVisible) {
		updateLocation();		//has to happen even if not selected, in case video is still moving when another one is selected
		
		//now thisX, thisY (and thisZ?) will have been updated for the scene
		//be sure details know this, and update their own locations RELATIVE to the scene
		
		for (int i=0; i<numOfDetails; i++) {
			theDetails[i].update(thisX, thisY, thisZ); //maybe dont need to pass x&y?
		}
	}
}

void Scene::draw() {
	if (isVisible) {
		ofPushMatrix();
		
		ofTranslate(thisX, thisY, thisZ);
		ofRotate(ROT);					//wants degrees
		
		panorama.draw(0,0);
		
		float xoffset = -2560/2;		//centering compensation for Details
		float yoffset = -300/2;
		ofTranslate(xoffset, yoffset, 0);
		
		for (int i=0; i<numOfDetails; i++) {
			theDetails[i].draw(thisZ+i); //<< ha!?
		}
		
		ofPopMatrix();
	}
}


//called from TUIO events in testApp -------------------------
void Scene::show() {
    isVisible = true;
	cout << "Scene ID "<<ID<<" should be visible."<<endl;
	//and stop/reset hiding timer
}
void Scene::hide() {
	//WIP implement a timer to delay onset of hiding
    //isVisible = false;
}
void Scene::setTargetLocPct (float _px, float _py) { //as percentages of entire screen
    isMoving = true;
    targetX = 1400*_px; //this display is 1400x1400; 
    targetY = (1400*_py)-(1400*yOffsetPct); //crude calibration
}
void Scene::setRotation(float _angradians) { //range is 0.0 to 6.28 radians at 360°
    rotMgr.setRotation(_angradians);
	rotMgr.updateRotation();
}
//------------------------------------------------


void Scene::updateLocation() { //automatic translation to clicked or target location
	
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


//FOR TESTING, respond to keys and mouse ==========================

//called from a mouseclick
void Scene::setTargetLocation (float _xt, float _yt) {
    isMoving = true;
    targetX = _xt; 
    targetY = _yt;
}

//called when selection changes in main by keyReleased handler
//BEWARE?, your z-level shifts have to account for the details on top of their scenes!
void Scene::setSelected(bool b) {	
    isSelected = b;
	//move to front if this is selected
	if (isSelected) {
		thisZ = total+1;
	} else {
		thisZ = ID;
	}
}

//...also from keyReleased handler, only to the selected scene...
void Scene::setRotation(bool _keyleft, bool _keyright, bool _keyup, bool _keydown) { //will be {keyleft,keyup,keyright,keydown} booleans
    rotMgr.setRotation(_keyleft,_keyright);
	rotMgr.updateRotation();
}
//=================================================================
