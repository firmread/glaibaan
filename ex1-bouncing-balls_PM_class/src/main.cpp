#include "ofMain.h"				//be sure copied older examples have this
#include "testApp.h"
#include "ofAppGlutWindow.h"	//be sure copied older examples have this

int main() {
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 800, 500, OF_WINDOW);
	ofRunApp( new testApp());
}
