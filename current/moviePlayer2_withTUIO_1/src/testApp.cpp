#include "testApp.h"

//version with no overlaid mini-scenes

//BEHAVIOR:
//Fiducial added -or- Mousedown : video appears
//Fiducial moves -or- Mouse drags,arrow keys pressed : video translates (& rotates)
//FIducial disappears -or- Mouse released : video freezes&fades, Text appears


//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetLogLevel(OF_LOG_ERROR); //suppress the message OF_LOG_WARNING: ofGLRenderer::draw(): texture is not allocated 
	
	ofBackground(255,255,255);
	glEnable(GL_DEPTH_TEST); //required to recognize z-axis positions

	selection = 1;			//to start, but level wont bump to front until an event
	
	initScenes();
	
	WW = float(ofGetWidth());
	WH = float(ofGetHeight());
	
#if USETUIO
	ofAddListener(tuioClient.objectAdded,this,&testApp::tuioAdded);
	ofAddListener(tuioClient.objectRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuioClient.objectUpdated,this,&testApp::tuioUpdated);
	tuioClient.start(3333);
#endif
}

void testApp::initScenes() {	//adds all the media at once //WIP why is text.png not opaque?
	//dont forget to change NUMOFSCENES in .h when you add more scenes
	
	theScenes[0] = new Scene(1024,768,"mov/trainpass1024.mov","textextext-o.png",NUMOFSCENES,1);
	//(int _w of clip, int _h of clip, string _bigmovfilename, _txtimgname, int _total, int _id of this scene)
	theScenes[1] = new Scene(640,480,"mov/ForestStream-h264.mov","textextext-o.png",NUMOFSCENES,2);
	
	
	
	for (int i=0; i<NUMOFSCENES; i++) {
		theScenes[i]->setup();
	}
	
	cout << "Scene(s) are initted." << endl;
	
	//testPicture.loadImage("mugunghwa-sm.jpg");
}

//--------------------------------------------------------------
void testApp::update(){

#if USETUIO
	tuioClient.getMessage();
#endif
	
	for (int i=0; i<NUMOFSCENES; i++) {
		theScenes[i]->update();
	}
	
	setPriority(); //separate routine in case of nuance
}

//--------------------------------------------------------------
void testApp::draw(){
	
#if USETUIO
	tuioClient.drawObjects();			//could nest this in a debug wrapper
#endif

	for (int i=0; i<NUMOFSCENES; i++) {
		theScenes[i]->draw();
	}
	
	//testing the effect of blending on the entire scene
	//testPicture.draw(0,0);
	
	report(); //prints text in upper left corner if you want running data of some kind
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
			
		case '0':
			selection = 0; //"unselect all"
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
	
	if (selection<=NUMOFSCENES) {
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
	//tell the selected clip what the arrow keypresses may be
	if ((key > 350)&&(selection!=0)) {
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
	if (selection!=0) {
		theScenes[selection-1]->setRotation(keyleft, keyright, keyup, keydown);
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if (selection!=0) {
	theScenes[selection-1]->setTargetLocPct(x/WW, y/WH);
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if (selection!=0) {
	theScenes[selection-1]->showAnimation();
	//tell the selected clip (in front) about this location
	theScenes[selection-1]->setTargetLocPct(x/WW, y/WH);
	}
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if (selection!=0) {
	
	theScenes[selection-1]->pauseAnimationSoon();
	}
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo info){ 

}
//-----DEBUGGING ON SCREEN---------------------------------------
//for onscreen data
string testApp::getUserStatus() {
	string s="";
	bool selected;
	for (int i=0; i < NUMOFSCENES; i++) {
		selected = theScenes[i]->isSelected;
			if (selected) {
				s = s+"["+ofToString(i+1)+"] ";
			} else {
				s = s+" "+ofToString(i+1)+"  ";
			}
		}
	return s;
}

void testApp::report() {
	ofPushMatrix();
	ofTranslate(10, 10, 0); //make room for the type....
	ofPushStyle();
	
    ofSetHexColor(0xFF0000);
    
	ofDrawBitmapString("Scenes [selected]="+getUserStatus(),0,0);
	//ofDrawBitmapString("hello",0,0);
	
	ofPopStyle();
	ofPopMatrix();
	
}


#if USETUIO

//----selection priority "logic"__________________________________

void testApp::setPriority() {  //called in update loop
	
	for (int i=0; i<NUMOFSCENES; i++) {
		if (theScenes[i]->isMoving) {
			theScenes[i]->setSelected(true);	//causes scene to bump itself to the front
			//note: more than one can be "on top" with this logic
			//visual effect is a flickering in overlapping areas
			
		} else {
			theScenes[i]->setSelected(false);
		}
	}
    //and if NO scenes are selected: keep as selected the most recent but still active 
}


//-----TUIO EVENT CALLBACKS---------------------------------------
//NOTE the fiducial IDs are used in three places below...

void testApp::tuioAdded(ofxTuioObject &tuioObject){	
	cout << "TUIO object, added " << tuioObject.getFiducialId() << endl;
	switch (tuioObject.getFiducialId()) {
		case 17:
			//tell a clip 
			theScenes[0]->showAnimation();
			break;
		case 14:
			theScenes[1]->showAnimation();
			break;
		default:
			break;
	}
    //this does not account for non-moving symbols
//    if (selection != prevselection) {
//		//update all the videos as to the selection state
//		for (int i=0; i < NUMOFSCENES; i++) {
//			if (i+1 != selection) {
//				theScenes[i]->setSelected(false);
//			}else {
//				theScenes[i]->setSelected(true);
//			}
//		}
//		prevselection = selection;
//	}

}

void testApp::tuioUpdated(ofxTuioObject &tuioObject){
	//cout << "TUIO object " << tuioObject.getFiducialId() << " updated at angle " << tuioObject.getAngle()<< " x= " << tuioObject.getXpos() <<endl;
	int sel;
	switch (tuioObject.getFiducialId()) {
		case 17:
			sel=1; //selection = 1;
			theScenes[sel-1]->setRotation(tuioObject.getAngle());
			theScenes[sel-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 14:
			sel=2; //selection = 2;
			theScenes[sel-1]->setRotation(tuioObject.getAngle());
			theScenes[sel-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		default:
			break;
	}

}

void testApp::tuioRemoved(ofxTuioObject &tuioObject){
	cout << "TUIO object, removed " << tuioObject.getFiducialId() << endl;
	switch (tuioObject.getFiducialId()) {
		case 17:
			theScenes[0]->pauseAnimationSoon();
			break;
		case 14:
			theScenes[1]->pauseAnimationSoon();
			break;
		default:
			break;
	}
}
#endif
//that endif is for the preprocessor directive USETUIO above
