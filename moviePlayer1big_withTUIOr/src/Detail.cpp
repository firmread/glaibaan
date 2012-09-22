/*
 *  Detail.cpp
 *  moviePlayer1big_withTUIO
 *
 *  Created by psm on 4/9/12.
 *  WIP 4/17/12
 *
 */

#include "Detail.h"
#include "ofVideoPlayer.h"

Detail::Detail(){};

void Detail::initYourself(string _videofile, float _x, float _y) {
	animation.loadMovie(_videofile);
	xoffset = _x;
	yoffset = _y;
}

void Detail::setup() {
	cout << "Setting up a detail at "<<xoffset<<" "<<yoffset<<endl;
	animation.play();
	animation.setLoopState(OF_LOOP_NORMAL); //looping for testing, use OF_LOOP_NONE for not
	//no animation.setAnchorPercent(0.5,0.5);
}

void Detail::update(float sceneX, float sceneY, float sceneZ) { //we dont need X & Y
	animation.idleMovie();	//required by ofVideoPlayer
	zlevel = sceneZ;
}

//happens after trans & rot draw of scene
void Detail::draw(float _zlevel) {
	//translates to zlevel+1?? yes please
	ofPushMatrix();
	ofTranslate(xoffset,yoffset, _zlevel);
	animation.draw(0,0);
	ofPopMatrix();
}