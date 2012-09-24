#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"


//========================================================================
int main( ){
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

	//1280,640
    // this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
