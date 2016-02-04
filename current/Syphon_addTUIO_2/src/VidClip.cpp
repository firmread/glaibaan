/*
 *  Detail.cpp
 *  moviePlayer1big_withTUIO
 *
 *  Created by psm on 4/9/12.
 *  WIP 4/17/12
 *
 */

#include "VidClip.h"
#include "ofVideoPlayer.h"

VidClip::VidClip(){};  //use this when not saying "new"?

void VidClip::init(string _movfilename, float _x, float _y) {
	clip.loadMovie(_movfilename); //in bin directory of this project
	xoffset = _x;
	yoffset = _y;
	clipAlpha = 255.0f;
	alphaState = OPAQUE;
};

void VidClip::setup() {
	cout << "Setting up a VidClip at "<<xoffset<<" "<<yoffset<<endl;
	clip.play();
	clip.setLoopState(OF_LOOP_NORMAL); //looping for testing, use OF_LOOP_NONE for not
	//no animation.setAnchorPercent(0.5,0.5);
}

void VidClip::play() {
	if (alphaState!=OPAQUE) alphaState=FADINGUP;
	
	clip.play();
}

void VidClip::update(float sceneZ) { //we dont need X & Y
	clip.idleMovie();	//required by ofVideoPlayer
	zlevel = sceneZ;
	updateAlpha();
}

//happens after trans & rot draw of scene
void VidClip::draw(float _zlevel) {
	
	ofPushMatrix();
		ofEnableAlphaBlending(); //interesting: color can also be set BEFORE ofEnableAlphaBlending
			ofSetColor(255,255,255,clipAlpha);
			ofTranslate(xoffset,yoffset, _zlevel); //assures we're at the center of the clip
			clip.draw(0,0);
		ofDisableAlphaBlending();
	ofPopMatrix();
}

void VidClip::pause(float _zlevel) { //call this in a draw loop
	if (alphaState!=GHOSTED) alphaState=FADINGDOWN;
	
	clip.stop();
	draw(_zlevel);
}

void VidClip::updateAlpha() { //call in the draw loop always
	float ghostLevel = 125.0f; //<-- EDIT here 
	
	switch (alphaState) {
			
		case OPAQUE :
			clipAlpha = 255.0f;
			break;
			
		case GHOSTED :
			clipAlpha = ghostLevel;
			break;
			
		case FADINGUP:
			//should be fading-in, so add to the opacity
			clipAlpha += 5.0f;      //<--EDIT to change speed of fade
			if (clipAlpha >= 255.0f) {
				alphaState=OPAQUE;
				clipAlpha = 255.0f;
			} 
			break;
			
		case FADINGDOWN :
			//should be fading out, so reduce the opacity
			clipAlpha -= 1.0f;     //<--EDIT to change speed of fade
			if (clipAlpha <= ghostLevel) {
				alphaState=GHOSTED;
				clipAlpha = ghostLevel;
			} 
			break;
	}
}
