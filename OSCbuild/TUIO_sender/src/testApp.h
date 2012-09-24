//moviePlayer2_withTUIO

#pragma once

#include "ofMain.h"
#include "ofxTuio.h"
#include "ofxOsc.h"

#define HOST "localhost"
//192.168.0.104
//localhost
#define PORT 12345

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
	
    //Osc
    ofxOscSender sender;
	
#ifdef USE_TUIO
	myTuioClient tuioClient;
	
	void	tuioAdded(ofxTuioObject & tuioObject);
	void	tuioRemoved(ofxTuioObject & tuioObject);
	void	tuioUpdated(ofxTuioObject & tuioObject);
#endif
 
};

