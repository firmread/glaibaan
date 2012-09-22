/*
 *  Bouncer.cpp
 *  ex1-bouncing-balls_PM_class
 *
 *  logic by Rick Companje, cloned by Mackey on 4/3/12.
 *  
 *
 */

#include "Bouncer.h"

Bouncer::Bouncer(int _id)			//constructor
{
	id = _id;
	
	//set start position and velocity
	pos = ofPoint(ofRandomWidth(), ofRandomHeight());
	vel = ofPoint(ofRandomf(), ofRandomf());
	
	//load image
	image.loadImage(ofToString(id % 6 + 1) + ".png");  //1..6
	image.setAnchorPercent(0.5, 0.5);
	
	//load sound
	sound.loadSound(ofToString(id % 4 + 1) + ".mp3");  //1..4
	sound.setVolume(ofRandomuf());
}

void Bouncer::update() {
	
	//gravity
	vel.y = vel.y + .1;
	
	//friction
	vel *= .9999;
	
	//horizontal boundaries
	if (!ofInRange(pos.x, 0, ofGetWidth())) { 
		vel.x *= -1; 
		pos.x = ofClamp(pos.x, 0, ofGetWidth()); 
		sound.play();
	}
	
	//vertical boundaries
	if (!ofInRange(pos.y, 0, ofGetHeight())) { 
		vel.y *= -1; 
		pos.y = ofClamp(pos.y, 0, ofGetHeight()); 
		sound.play(); 
	}
	
	//update pos
	pos += vel;
	
}


void Bouncer::draw() {
	
	image.draw(pos.x, pos.y, 100, 100);
	
}