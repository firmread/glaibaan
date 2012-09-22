/*
 *  testApp.h
 *  openFrameworks
 *
 *  by Rick Companje
 *  modified to use a Class by mackey DDA pratt
 */
 
#pragma once

#define NUM 10

#include "ofMain.h"
#include "Bouncer.h"			//because this refers to Bouncer class	

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	// list of Bouncers	
	Bouncer*	theBouncers[NUM]; //basic array notation


};

