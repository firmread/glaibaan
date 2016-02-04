#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxSyphon.h"
#include "Scene.h"
#include "ofxTuio.h"


#ifndef NUMOFSCENES
#define NUMOFSCENES 8
#endif


#define USETUIO true	//using this to use/ignore tuio-related code vs just testing with mouse
//say false if just using mouse

class testApp : public ofBaseApp{
	
public:
	
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
	
	void	setPriority();
	
	// collections of video clip animations with textimages
	Scene*		theScenes[NUMOFSCENES];
	
	float WW, WH;	//window dimensions
	
	ofImage	testPicture;
    
    string  getUserStatus();
    
    //Syphon
    ofTexture tex;
    
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer individualTextureSyphonServer;
	
	ofxSyphonClient mClient;
    
	//ofImage foggy;
	
#if USETUIO
	myTuioClient tuioClient;
	void	tuioAdded(ofxTuioObject & tuioObject);
	void	tuioRemoved(ofxTuioObject & tuioObject);
	void	tuioUpdated(ofxTuioObject & tuioObject);
#endif

};

#endif

