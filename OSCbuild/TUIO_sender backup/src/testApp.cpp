//moviePlayer2_withTUIO
//The TUIO event callbacks are at the bottom of this page.

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	glEnable(GL_DEPTH_TEST); //required to recognize z-axis position

	selection = 1;			//to start, but level wont bump to front until a keypress
	
	initVideoList();
    
    ofSetWindowTitle("TUIO to OSC sender");
	
    // open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
    
    
#ifdef USE_TUIO
	ofAddListener(tuioClient.objectAdded,this,&testApp::tuioAdded);
	ofAddListener(tuioClient.objectRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuioClient.objectUpdated,this,&testApp::tuioUpdated);
	
	tuioClient.start(3333);
#endif
	
}

//--------------------------------------------------------------

void testApp::initVideoList() {	//adds all the videos at once with default starting locations
	
	theVideos[0] =( new VideoClip (0, 0, 2560, 300, "movies/BGimage.jpg",NUMOFCLIPS, 1) );
	theVideos[1] = ( new VideoClip (800, 200, 1000, 726, "movies/timessqColor.mov",NUMOFCLIPS, 2) );
	theVideos[2] = ( new VideoClip (0, 490, 720, 480, "movies/timessqColor.mov",NUMOFCLIPS, 3) );
	theVideos[3] = ( new VideoClip (730, 490, 720, 480, "movies/timessqColor.mov",NUMOFCLIPS, 4) );
    theVideos[4] = ( new VideoClip (0, 490, 720, 480, "movies/timessqColor.mov",NUMOFCLIPS, 5) );
	theVideos[5] = ( new VideoClip (730, 490, 720, 480, "movies/timessqColor.mov",NUMOFCLIPS, 6) );
	cout << "Videos are ready." << endl;
}

//--------------------------------------------------------------
void testApp::update(){
	
#ifdef USE_TUIO  
	tuioClient.getMessage();
#endif
	
	for (int i=0; i<NUMOFCLIPS; i++) {
		theVideos[i]->update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){

#ifdef USE_TUIO //------------------ TUIO 
	//dont care! tuioClient.drawCursors();
	tuioClient.drawObjects(); 
#endif
	
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

#ifdef USE_TUIO
//NOTE the fiducial IDs are used in three places below...

void testApp::tuioAdded(ofxTuioObject &tuioObject){	
	cout << "TUIO object, added " << tuioObject.getFiducialId() << endl;
	ofxOscMessage m;
    switch (tuioObject.getFiducialId()) {
		case 12:
			//tell a clip 
			//theVideos[0]->show();
            //tell OSC
            m.setAddress("/mark1/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
        case 13:
			//tell a clip 
			//theVideos[1]->show();
            //tell OSC
            m.setAddress("/mark2/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
		case 14:
			//tell a clip 
			//theVideos[2]->show();
            //tell OSC
            m.setAddress("/mark3/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
		case 15:
			//theVideos[3]->show();
            //tell OSC
            m.setAddress("/mark4/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
        case 16:
			//tell a clip 
			//theVideos[4]->show();
            //tell OSC
            m.setAddress("/mark5/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
		case 17:
			//theVideos[5]->show();
            //tell OSC
            m.setAddress("/mark6/show");
            m.addIntArg(1);
            sender.sendMessage(m);
		default:
			break;
	}
}

void testApp::tuioUpdated(ofxTuioObject &tuioObject){
	//cout << "TUIO object " << tuioObject.getFiducialId() << " updated at angle " << tuioObject.getAngle()<< " x= " << tuioObject.getXpos() <<endl;
    ofxOscMessage m;
	
	switch (tuioObject.getFiducialId()) {
		case 12:
			//selection = 1;
			//theVideos[selection-1]->setRotation(tuioObject.getAngle());
			//theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
            m.setAddress("/mark1/angle");
            m.addFloatArg(tuioObject.getAngle());
            sender.sendMessage(m);
            m.setAddress("/mark1/x");
            m.addIntArg(tuioObject.getXpos());
            sender.sendMessage(m);
            m.setAddress("/mark1/y");
            m.addIntArg(tuioObject.getYpos());
            sender.sendMessage(m);
			break;
        case 13:
//			selection = 2;
//			theVideos[selection-1]->setRotation(tuioObject.getAngle());
//			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
            m.setAddress("/mark2/angle");
            m.addFloatArg(tuioObject.getAngle());
            sender.sendMessage(m);
            m.setAddress("/mark2/x");
            m.addIntArg(tuioObject.getXpos());
            sender.sendMessage(m);
            m.setAddress("/mark2/y");
            m.addIntArg(tuioObject.getYpos());
            sender.sendMessage(m);
			break;
		case 14:
//			selection = 3;
//			theVideos[selection-1]->setRotation(tuioObject.getAngle());
//			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
            m.setAddress("/mark3/angle");
            m.addFloatArg(tuioObject.getAngle());
            sender.sendMessage(m);
            m.setAddress("/mark3/x");
            m.addIntArg(tuioObject.getXpos());
            sender.sendMessage(m);
            m.setAddress("/mark3/y");
            m.addIntArg(tuioObject.getYpos());
            sender.sendMessage(m);
			break;
		case 15:
//			selection = 4;
//			theVideos[selection-1]->setRotation(tuioObject.getAngle());
//			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
            m.setAddress("/mark4/angle");
            m.addFloatArg(tuioObject.getAngle());
            sender.sendMessage(m);
            m.setAddress("/mark4/x");
            m.addIntArg(tuioObject.getXpos());
            sender.sendMessage(m);
            m.setAddress("/mark4/y");
            m.addIntArg(tuioObject.getYpos());
            sender.sendMessage(m);
			break;
        case 16:
//			selection = 5;
//			theVideos[selection-1]->setRotation(tuioObject.getAngle());
//			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
            m.setAddress("/mark5/angle");
            m.addFloatArg(tuioObject.getAngle());
            sender.sendMessage(m);
            m.setAddress("/mark5/x");
            m.addIntArg(tuioObject.getXpos());
            sender.sendMessage(m);
            m.setAddress("/mark5/y");
            m.addIntArg(tuioObject.getYpos());
            sender.sendMessage(m);
			break;
        case 17:
//			selection = 6;
//			theVideos[selection-1]->setRotation(tuioObject.getAngle());
//			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
            m.setAddress("/mark6/angle");
            m.addFloatArg(tuioObject.getAngle());
            sender.sendMessage(m);
            m.setAddress("/mark6/x");
            m.addIntArg(tuioObject.getXpos());
            sender.sendMessage(m);
            m.setAddress("/mark6/y");
            m.addIntArg(tuioObject.getYpos());
            sender.sendMessage(m);
        
		default:
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
}

void testApp::tuioRemoved(ofxTuioObject &tuioObject){
	cout << "TUIO object, removed " << tuioObject.getFiducialId() << endl;
    ofxOscMessage m;
	switch (tuioObject.getFiducialId()) {
		case 12:
//			theVideos[0]->hide();
            //tell OSC
            m.setAddress("/mark1/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
		case 13:
//			theVideos[1]->hide();
            //tell OSC
            m.setAddress("/mark2/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
        case 14:
//			theVideos[2]->hide();
            //tell OSC
            m.setAddress("/mark3/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
		case 15:
//			theVideos[3]->hide();
            //tell OSC
            m.setAddress("/mark4/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
        case 16:
//			theVideos[4]->hide();
            //tell OSC
            m.setAddress("/mark5/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
        case 17:
//			theVideos[5]->hide();
            //tell OSC
            m.setAddress("/mark6/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
		default:
			break;
	}
}
#endif


