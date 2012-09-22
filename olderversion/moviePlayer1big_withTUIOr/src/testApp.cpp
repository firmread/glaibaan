#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	glEnable(GL_DEPTH_TEST); //required to recognize z-axis positions

	selection = 1;			//to start, but level wont bump to front until an event
	
	initScenes();
	
	ofAddListener(tuioClient.objectAdded,this,&testApp::tuioAdded);
	ofAddListener(tuioClient.objectRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuioClient.objectUpdated,this,&testApp::tuioUpdated);
	
	tuioClient.start(3333);
}

void testApp::initScenes() {	//adds all the media at once with relative locations on each scene BG
	//dont forget to change NUMOFSCENES in .h when you add more scenes
	
	// 2560/2 = 1280
	// display width? testing 1400, so to see center of pano: -1280+(1400/2)=-580
	
	theScenes[0] = new Scene(-580,450,2560,300,"BG1image.jpg",1,1); 
	//(int _x, int _y, int _w, int _h, string _BGfilename, int _total, int _id)
	
	theScenes[0] -> initDetail("movies/movingboatPlainVDO.mov",800.0,200.0); //locs within the scene
	theScenes[0] -> initDetail("movies/movingbird.mov",1400.0,0.0);
	theScenes[0] -> initDetail("movies/blinkinglights.mov",1700.0,0.0);
	
	for (int i=0; i<NUMOFSCENES; i++) {
		theScenes[i]->setup();
	}
	
	
	cout << "Scene & details are initted." << endl;
}

//--------------------------------------------------------------
void testApp::update(){
	
	tuioClient.getMessage();
	
	for (int i=0; i<NUMOFSCENES; i++) {
		theScenes[i]->update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	tuioClient.drawObjects();			//could nest this in a debug wrapper
	
	for (int i=0; i<NUMOFSCENES; i++) {
		theScenes[i]->draw();
	}
		
	report();
}

//FOR TESTING, using keys and mouse--------------------------------------------------------------

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
		for (int i=0; i < NUMOFSCENES; i++) {
			if (i+1 != selection) {
				theScenes[i]->setSelected(false);
			}else {
				theScenes[i]->setSelected(true);
			}
		}
		prevselection = selection;
	}
	//tell the selected clip what the arrow keypresses may be
	if (key > 350) {
		theScenes[selection-1]->setRotation(keyleft, keyright, keyup, keydown);
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
	theScenes[selection-1]->setRotation(keyleft, keyright, keyup, keydown);
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
	theScenes[selection-1]->setTargetLocation(mouseX, mouseY);
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

//-----TUIO EVENT CALLBACKS---------------------------------------
//NOTE the fiducial IDs are used in three places below...

void testApp::tuioAdded(ofxTuioObject &tuioObject){	
	cout << "TUIO object, added " << tuioObject.getFiducialId() << endl;
	switch (tuioObject.getFiducialId()) {
		case 17:
			//tell a clip 
			theScenes[0]->show();
			break;
//		case 18:
//			theScenes[1]->show();
//			break;
		default:
			break;
	}
}

void testApp::tuioUpdated(ofxTuioObject &tuioObject){
	//cout << "TUIO object " << tuioObject.getFiducialId() << " updated at angle " << tuioObject.getAngle()<< " x= " << tuioObject.getXpos() <<endl;
	
	switch (tuioObject.getFiducialId()) {
		case 17:
			selection = 1;
			theScenes[selection-1]->setRotation(tuioObject.getAngle());
			theScenes[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
//		case 18:
//			selection = 2;
//			theScenes[selection-1]->setRotation(tuioObject.getAngle());
//			theScenes[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
//			break;
		default:
			break;
	}
	if (selection != prevselection) {
		//update all the videos as to the selection state 
		for (int i=0; i < NUMOFSCENES; i++) {
			if (i+1 != selection) {
				theScenes[i]->setSelected(false);
			}else {
				theScenes[i]->setSelected(true);
			}
		}
		prevselection = selection;
	}
}

void testApp::tuioRemoved(ofxTuioObject &tuioObject){
	cout << "TUIO object, removed " << tuioObject.getFiducialId() << endl;
	switch (tuioObject.getFiducialId()) {
		case 17:
			theScenes[0]->hide();
			break;
//		case 18:
//			theScenes[1]->hide();
//			break;
		default:
			break;
	}
}

