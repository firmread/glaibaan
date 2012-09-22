//moviePlayer2_withTUIO
//The TUIO event callbacks are at the bottom of this page.

#include "testApp.h"
const int width = 800;
const int height = 600;

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	glEnable(GL_DEPTH_TEST); //required to recognize z-axis position

    
    //add for syphon
    mainOutputSyphonServer.setName("Screen Output");
	individualTextureSyphonServer.setName("Texture Output");
    
	mClient.setup();
    
    mClient.setApplicationName("Simple Server");
    mClient.setServerName("");
	
    tex.allocate(width, height, GL_RGBA);
    
    //
    
	selection = 1;			//to start, but level wont bump to front until a keypress
	
	initVideoList();
	
#ifdef USE_TUIO
	ofAddListener(tuioClient.objectAdded,this,&testApp::tuioAdded);
	ofAddListener(tuioClient.objectRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuioClient.objectUpdated,this,&testApp::tuioUpdated);
	
	tuioClient.start(3333);
#endif
	
}



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

    
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
#ifdef USE_TUIO //------------------ TUIO 
	//dont care! tuioClient.drawCursors();
	tuioClient.drawObjects(); 
#endif
	
	ofSetHexColor(0xFFFFFF);		//for some reason
	
	for (int i=0; i<NUMOFCLIPS; i++) {
		theVideos[i]->draw();
	}
		
	report();
    
    
    
    
    // draw static into our one texture.
    unsigned char pixels[200*100*4];
    
    for (int i = 0; i < 200*100*4; i++)
    {
        pixels[i] = (int)(255 * ofRandomuf());
    }
    tex.loadData(pixels, 200, 100, GL_RGBA);
    
    tex.draw(50, 50);
    
    
	// Syphon Stuff
    
    ofSetColor(255, 255, 255);
    
    ofEnableAlphaBlending();
    
    mClient.draw(50, 50);
    
	mainOutputSyphonServer.publishScreen();
    
    individualTextureSyphonServer.publishTexture(&tex);

    
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
	switch (tuioObject.getFiducialId()) {
		case 12:
			//tell a clip 
			theVideos[4]->show();
			break;
        case 15:
			//tell a clip 
			theVideos[5]->show();
			break;
		case 16:
			//tell a clip 
			theVideos[0]->show();
			break;
		case 17:
			theVideos[1]->show();
			break;
        case 18:
			//tell a clip 
			theVideos[2]->show();
			break;
		case 19:
			theVideos[3]->show();
		default:
			break;
	}
}

void testApp::tuioUpdated(ofxTuioObject &tuioObject){
	//cout << "TUIO object " << tuioObject.getFiducialId() << " updated at angle " << tuioObject.getAngle()<< " x= " << tuioObject.getXpos() <<endl;
	
	switch (tuioObject.getFiducialId()) {
		case 12:
			selection = 5;
			theVideos[selection-1]->setRotation(tuioObject.getAngle());
			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
        case 15:
			selection = 6;
			theVideos[selection-1]->setRotation(tuioObject.getAngle());
			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 16:
			selection = 1;
			theVideos[selection-1]->setRotation(tuioObject.getAngle());
			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 17:
			selection = 2;
			theVideos[selection-1]->setRotation(tuioObject.getAngle());
			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
        case 18:
			selection = 3;
			theVideos[selection-1]->setRotation(tuioObject.getAngle());
			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
        case 19:
			selection = 4;
			theVideos[selection-1]->setRotation(tuioObject.getAngle());
			theVideos[selection-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
        
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
	switch (tuioObject.getFiducialId()) {
		case 12:
			theVideos[4]->hide();
			break;
		case 15:
			theVideos[5]->hide();
			break;
        case 16:
			theVideos[0]->hide();
			break;
		case 17:
			theVideos[1]->hide();
			break;
        case 18:
			theVideos[2]->hide();
			break;
        case 19:
			theVideos[3]->hide();
			break;
		default:
			break;
	}
}
#endif


