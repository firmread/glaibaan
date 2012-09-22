#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	glEnable(GL_DEPTH_TEST); //required to recognize z-axis position

	selection = 1;			//to start, but level wont bump to front until a keypress
	
	initVideoList();
}

void testApp::initVideoList() {	//adds all the videos at once with default starting locations
	
	theVideos[0] =( new VideoClip (0, 0, 640, 480, "movies/ForestStream-h264.mov",NUMOFCLIPS, 1) );
	theVideos[1] = ( new VideoClip (650, 0, 640, 480, "movies/deer-h264.mov",NUMOFCLIPS, 2) );
	theVideos[2] = ( new VideoClip (0, 490, 720, 480, "movies/Alex622.mov",NUMOFCLIPS, 3) );
	theVideos[3] = ( new VideoClip (730, 490, 720, 480, "movies/Piyatas622.mov",NUMOFCLIPS, 4) );
	cout << "Videos are initted." << endl;
}

//--------------------------------------------------------------
void testApp::update(){
	for (int i=0; i<NUMOFCLIPS; i++) {
		theVideos[i]->update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetHexColor(0xFFFFFF);		//for some reason
	
	for (int i=0; i<NUMOFCLIPS; i++) {
		theVideos[i]->draw();
	}
		
	report();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
	//cout << "That was key: " << key << endl;
	
	//for letter keys, use single quotes not double
	switch (key) {
		case 356: // left? key  //these may be MAC OS only codes
			keyleft = true;
			break;
		case 357: // up key
			keyup = true;
			break;
		case 358: // right? key
			keyright = true;
			break;
		case 359: // down key
			keydown = true;
			break;
			
		case '1':   //selection is a global in main, which movie to control
			selection = 1; //first rect
			break;
			
		case '2':
			selection = 2; //second rect
			break;
			
		case '3':   
			selection = 3; 
			break;
			
		case '4':
			selection = 4; 
			break;
			
		case 'd': // use as the "right" command
			keyright = true;
			break;
		case 'a':
			keyleft = true;
			break;
		case 'w': // "up"
			keyup = true;
			break;
		case 's':
			keydown = true;
			break;
	}
	
	if (selection != prevselection) {
		//update all the videos as to the selection state 
		for (int i=0; i < NUMOFCLIPS; i++) {
			if (i+1 != selection) {
				theVideos[i]->setSelected(false);
			}else {
				theVideos[i]->setSelected(true);
			}
		}
		prevselection = selection;
	}
	//tell the selected clip what the arrow keypresses may be
	if (key > 350) {
		theVideos[selection-1]->setRotation(keyleft, keyright, keyup, keydown);
	}
	//reset them to false on keyReleased
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch (key) {
		case 356: // left key  //these may be MAC OS only codes
			keyleft = false;
			break;
		case 357: // up key
			keyup = false;
			break;
		case 358: // right? key
			keyright = false;
			break;
		case 359: // down key
			keydown = false;
			break;
		case 'd': // use as the "right" command
			keyright = false;
			break;
		case 'a':
			keyleft = false;
			break;
		case 'w': // "up"
			keyup = false;
			break;
		case 's':
			keydown = false;
			break;
	}
	//again tell the selected clip what the arrow keys released may be, to zero-out
	theVideos[selection-1]->setRotation(keyleft, keyright, keyup, keydown);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){


}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	//tell the selected clip (in front) about this location
	theVideos[selection-1]->setTargetLocation(mouseX, mouseY);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo info){ 
	
	//dragPt = info.position;
//	
//	forestX = dragPt.x;
//	forestY = dragPt.y;

}
//-----DEBUGGING ON SCREEN---------------------------------------


void testApp::report() {
	ofPushMatrix();
	ofTranslate(10, 10, 0); //make room for the type....
	ofPushStyle();
	
    ofSetHexColor(0xFF0000);
	//ofDrawBitmapString("isPressed="+ofToString(isPressed),20,0);
	ofDrawBitmapString("hello",0,0);
	
	ofPopStyle();
	ofPopMatrix();
	
}


