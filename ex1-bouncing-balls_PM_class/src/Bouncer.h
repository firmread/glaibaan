/*
 *  Bouncer.h
 *  ex1-bouncing-balls_PM_class
 *
 *  Cloned by Mackey on 4/3/12.
 *  
 */

#pragma once
#include "ofMain.h"			//since this uses oF core classes ofPoint, ofImage, ofSoundPlayer

class Bouncer {

public:
	Bouncer(int _id);				//constructor
	
	int				id;
	ofPoint			pos,vel;
	ofImage			image;
	ofSoundPlayer	sound;
	
	
	void	update();
	void	draw();

}; //dont forget the ; here!