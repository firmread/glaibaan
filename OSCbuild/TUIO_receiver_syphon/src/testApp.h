//moviePlayer2_withTUIO

#pragma once

#include "ofMain.h"
#include "VideoClip.h"
#include "ofxTuio.h"

#ifndef NUMOFCLIPS
#define NUMOFCLIPS 6
#endif
#ifndef USE_TUIO
#define USE_TUIO true
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
	
	void initVideoList();	//all at once
	
	// properties
	bool	frameByframe, isPressed;
	int		selection,prevselection;
	bool	keyleft, keyright, keyup, keydown;
	
	// list of video clips	
	VideoClip*	theVideos[NUMOFCLIPS]; //basic array notation
    
    //osc
    ofxOscReceiver receiver;
    
    int x0,y0,x1,y1,x2,y2,x3,y3,x4,y4,x5,y5;
};

