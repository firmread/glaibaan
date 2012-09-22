#pragma once

#include "ofMain.h"
#include "ofxTuio.h"
#include "Scene.h"

#ifndef NUMOFSCENES
#define NUMOFSCENES 1
#endif

class testApp : public ofBaseApp{
	
public:
	//the standard oF methods
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);	
	
	void report();
	
	void initScenes();	//all at once
	
	// properties
	bool	frameByframe, isPressed;
	int		selection,prevselection;
	bool	keyleft, keyright, keyup, keydown;
	
	// list of video clips	
	Scene*		theScenes[NUMOFSCENES];
	
	myTuioClient tuioClient;
	
	void	tuioAdded(ofxTuioObject & tuioObject);
	void	tuioRemoved(ofxTuioObject & tuioObject);
	void	tuioUpdated(ofxTuioObject & tuioObject);
};

