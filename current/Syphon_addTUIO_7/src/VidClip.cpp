/*
 *  VidClip.cpp
 *  
 *
 *  Created by psm on 4/9/12.
 *  WIP 4/17/12  0928
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
	alphaState = INVISIBLE;
};

void VidClip::setup() {
	cout << "Setting up a VidClip at "<<xoffset<<" "<<yoffset<<endl;
	//clip.play();
	//clip.setLoopState(OF_LOOP_NORMAL);
    //looping for testing, use OF_LOOP_NONE for not
    clip.setLoopState(OF_LOOP_NONE);
	reloopPctTime = 0.1; //<-- EDIT for example 10% into total length of clip
}

void VidClip::play() {
	//if ((alphaState==INVISIBLE)||(alphaState==INVISIBLE))
    alphaState=FADINGUP;
    printf("clip restarting from 0 \n");
    clip.setPosition(0); //restart from beginning
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
    
    //watch progress of the clip, rewind to restart point when at end
    if (clip.getPosition()>0.98) { //almost the end
		clip.setPosition(reloopPctTime); //percentage of total duration
		//printf("reset pos \n");
	}
}

void VidClip::pause(float _zlevel) { //call this in a draw loop
	clip.stop();
	draw(_zlevel);
}

void VidClip::updateAlpha() { //call in the loop always
    //printf("VidClip: updateAlpha() alphaState=%i\n",alphaState);
    
	float ghostLevel = 125.0f; //<-- EDIT here 
	
	switch (alphaState) {
			
		case FADINGUP:
			//should be fading-in, so add to the opacity
			clipAlpha += 5.0f;      //<--EDIT to change speed of fade
			if (clipAlpha >= 255.0f) {
				alphaState=OPAQUE;
				clipAlpha = 255.0f;
			} 
			break;
			
		case OPAQUE:
			clipAlpha = 255.0f;
			break;

		case FADETOGHOST:
			//should be fading out, so reduce the opacity
			clipAlpha -= 1.0f;     //<--EDIT to change speed of fade
			if (clipAlpha <= ghostLevel) {
				alphaState=GHOSTED;
				clipAlpha = ghostLevel;
			} 
			break;
            
		case GHOSTED:
			clipAlpha = ghostLevel;
			break;

		case FADINGOUT:  //0928
			//should be fading out, so reduce the opacity
			clipAlpha -= 1.0f;     //<--EDIT to change speed of fade
            //printf("clip fading out..........\n");
			if (clipAlpha <= 0) {
				alphaState=INVISIBLE;
				clipAlpha = 0.0f;
			}
			break;
            
		case INVISIBLE:  //0928
			break;
    }
}
//0928
void VidClip::setFadeOut() {
    //printf("VidClip: alphaState was %i, now FADINGOUT\n",alphaState);
    //from Scene when inactivity timeout is reached
    alphaState=FADINGOUT;
    
}
void VidClip::setGhosted() {
    //from Scene when text display delay timeout is reached
    alphaState=FADETOGHOST;
}
