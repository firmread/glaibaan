#include "testApp.h"


//version with no overlaid mini-scenes

//BEHAVIOR:
//Fiducial added -or- Mousedown : video appears
//Fiducial moves -or- Mouse drags,arrow keys pressed : video translates (& rotates)
//FIducial disappears -or- Mouse released : video freezes&fades, Text appears


//--------------------------------------------------------------
void testApp::setup(){
    
    ofEnableAlphaBlending();
	ofSetWindowTitle("Glaibaan 09/28/12");
    ofSetLogLevel(OF_LOG_ERROR); //suppress the message OF_LOG_WARNING: ofGLRenderer::draw(): texture is not allocated
	
	ofBackground(255,255,255);
	glEnable(GL_DEPTH_TEST); //required to recognize z-axis positions
    
	selection = 1;			//to start, but level wont bump to front until an event
	
	initScenes();
	
//	WW = float(ofGetWidth());
//	WH = float(ofGetHeight());
	
#if USETUIO
	ofAddListener(tuioClient.objectAdded,this,&testApp::tuioAdded);
	ofAddListener(tuioClient.objectRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuioClient.objectUpdated,this,&testApp::tuioUpdated);
	tuioClient.start(3333);
#endif
    
    //syphon
	mainOutputSyphonServer.setName("Screen Output");
	individualTextureSyphonServer.setName("Texture Output");

	mClient.setup();
    
    mClient.setApplicationName("Simple Server");
    mClient.setServerName("");
	
    tex.allocate(WW, WH, GL_RGBA);
    
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    //foggy.loadImage("foggy.png");
}

//--------------------------------------------------------------

void testApp::initScenes() {	//adds all the media at once //WIP why is text.png not opaque?
	//dont forget to change NUMOFSCENES in .h when you add more scenes
	
	theScenes[0] = new Scene(889,341,"mov/01ssseaport889.mov","01postcard.png",NUMOFSCENES,1);
	//(int _w of clip, int _h of clip, string _bigmovfilename, _txtimgname, int _total, int _id of this scene)
	theScenes[1] = new Scene(1000,646,"mov/02ctpwintercolor1137.mov","02postcard.png",NUMOFSCENES,2);
	theScenes[2] = new Scene(1179,852,"mov/03ctpsummer1179.mov","03postcard.png",NUMOFSCENES,3);
	theScenes[3] = new Scene(1280,906,"mov/04flatiron1208.mov","04postcard.png",NUMOFSCENES,4);
    theScenes[4] = new Scene(1600,740,"mov/DUMBO.mov","05postcard.png",NUMOFSCENES,5);
    theScenes[5] = new Scene(1000,726,"mov/timessqColor.mov","06postcard.png",NUMOFSCENES,6);
    theScenes[6] = new Scene(1000,646,"mov/02ctpwintercolor1137.mov","07postcard.png",NUMOFSCENES,7);
    theScenes[7] = new Scene(1000,646,"mov/02ctpwintercolor1137.mov","08postcard.png",NUMOFSCENES,8);
	
//	theScenes[0]->XOFFSET = 0.01;
//	theScenes[0]->YOFFSET = 0.01;
    
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

    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    
#if USETUIO
//	tuioClient.drawObjects();			//could nest this in a debug wrapper
#endif
    
    
    ofSetColor(255);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
	for (int i=0; i<NUMOFSCENES; i++) {
		theScenes[i]->draw();
        
	}
	//testing the effect of blending on the entire scene
	//testPicture.draw(0,0);
	
//    cout << "targetX of "+ ofToString(theScenes[0]->targetX)  << endl;
	report(); //prints text in upper left corner if you want running data of some kind
    
    
	// Syphon Stuff
    
    ofSetColor(255, 255, 255);

    ofEnableAlphaBlending();
    
    mClient.draw(50, 50);    
    
	mainOutputSyphonServer.publishScreen();
    
    individualTextureSyphonServer.publishTexture(&tex);
    
    //ofDrawBitmapString("Note this text is not captured by Syphon since it is drawn after publishing.\nYou can use this to hide your GUI for example.", 150,500);
    
    //foggy.draw(0, 0, ofGetWidth(), ofGetHeight());
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
		case 'f':
			ofToggleFullscreen();
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
//should be "the newest mover goes to the front"------------------

void testApp::setPriority() {  //called in update loop
	
	list<float> scenesTimeMoving;
    
    //look for anyone moving
	for (int i=0; i<NUMOFSCENES; i++) {
		if (theScenes[i]->isMoving) {
			
			//pm0928
			float tm = theScenes[i]->startedAnimTime;
			scenesTimeMoving.push_back(tm);
			
		}
	}
    if (scenesTimeMoving.size()>0) {
		//tell the newest one it is selected, unselect the others
		//(selection means "be on top")
        
		
		//debugging
		//cout << endl;;
		//printf("Before sort...\n");
        //list<float>::iterator it; //iterator for that list type
		//for(it=scenesTimeMoving.begin();it!=scenesTimeMoving.end();it++)
        ///printf(" %f\n",*it);
		
		scenesTimeMoving.sort();
		
		//debugging
		//cout << "After sort..." << endl;
		//for(it=scenesTimeMoving.begin();it!=scenesTimeMoving.end();++it)
        //printf(" %f\n",*it);
		
		float shortestTime=scenesTimeMoving.front();
		//now ask the scenes which one has this time (!)
		for (int i=0; i<NUMOFSCENES; i++) {
            if (shortestTime==(theScenes[i]->startedAnimTime)) {
                theScenes[i]->setSelected(true);
            } else {
				theScenes[i]->setSelected(false);
			}
        }
	}
    
}
//and if NO scenes are selected the layer priority is just by scene number




//-----TUIO EVENT CALLBACKS---------------------------------------
//NOTE the fiducial IDs are used in three places below...

void testApp::tuioAdded(ofxTuioObject &tuioObject){
//	cout << "TUIO object, added " << tuioObject.getFiducialId() << endl;
	switch (tuioObject.getFiducialId()) {
		case 106:
			//tell a clip
			theScenes[0]->showAnimation();
			break;
		case 69:
			theScenes[1]->showAnimation();
			break;
		case 63:
			theScenes[2]->showAnimation();
			break;
		case 1:
			theScenes[3]->showAnimation();
			break;
        case 29:
			theScenes[4]->showAnimation();
			break;
        case 11:
			theScenes[5]->showAnimation();
			break;
        case 49:
			theScenes[6]->showAnimation();
			break;
        case 75:
			theScenes[7]->showAnimation();
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
		case 106:
			sel=1; //selection = 1;
			theScenes[sel-1]->setRotation(tuioObject.getAngle());
			theScenes[sel-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 69:
			sel=2; //selection = 2;
			theScenes[sel-1]->setRotation(tuioObject.getAngle());
			theScenes[sel-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 63:
			sel=3; //selection = 3;
			theScenes[sel-1]->setRotation(tuioObject.getAngle());
			theScenes[sel-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 1:
			sel=4; //selection = 4;
			theScenes[sel-1]->setRotation(tuioObject.getAngle());
			theScenes[sel-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 29:
			sel=5; //selection = 5;
			theScenes[sel-1]->setRotation(tuioObject.getAngle());
			theScenes[sel-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 11:
			sel=6; //selection = 6;
			theScenes[sel-1]->setRotation(tuioObject.getAngle());
			theScenes[sel-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 49:
			sel=7; //selection = 7;
			theScenes[sel-1]->setRotation(tuioObject.getAngle());
			theScenes[sel-1]->setTargetLocPct(tuioObject.getXpos(), tuioObject.getYpos());
			break;
		case 75:
			sel=8; //selection = 8;
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
		case 106:
			theScenes[0]->pauseAnimationSoon();
			break;
		case 69:
			theScenes[1]->pauseAnimationSoon();
			break;
		case 63:
			theScenes[2]->pauseAnimationSoon();
			break;
		case 1:
			theScenes[3]->pauseAnimationSoon();
			break;
        case 29:
			theScenes[4]->pauseAnimationSoon();
			break;
        case 11:
			theScenes[5]->pauseAnimationSoon();
			break;
        case 49:
			theScenes[6]->pauseAnimationSoon();
			break;
        case 75:
			theScenes[7]->pauseAnimationSoon();
			break;
		default:
			break;
	}
}
#endif
//that endif is for the preprocessor directive USETUIO above


