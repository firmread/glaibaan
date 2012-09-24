//moviePlayer2_withTUIO
//The TUIO event callbacks are at the bottom of this page.

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	glEnable(GL_DEPTH_TEST); //required to recognize z-axis position
    
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
void testApp::update(){
	
#ifdef USE_TUIO  
	tuioClient.getMessage();
#endif
	
}

//--------------------------------------------------------------
void testApp::draw(){

#ifdef USE_TUIO //------------------ TUIO 
	//dont care! tuioClient.drawCursors();
	tuioClient.drawObjects(); 
#endif
	
	ofSetHexColor(0xFFFFFF);		//for some reason
	
		
	report();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
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
            m.setAddress("/mark1/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
        case 13:
            m.setAddress("/mark2/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
		case 14:
            m.setAddress("/mark3/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
		case 15:
            m.setAddress("/mark4/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
        case 16:
            m.setAddress("/mark5/show");
            m.addIntArg(1);
            sender.sendMessage(m);
			break;
		case 17:
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
}

void testApp::tuioRemoved(ofxTuioObject &tuioObject){
	cout << "TUIO object, removed " << tuioObject.getFiducialId() << endl;
    ofxOscMessage m;
	switch (tuioObject.getFiducialId()) {
		case 12:
            m.setAddress("/mark1/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
		case 13:
            m.setAddress("/mark2/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
        case 14:
            m.setAddress("/mark3/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
		case 15:
            m.setAddress("/mark4/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
        case 16:
            m.setAddress("/mark5/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
        case 17:
            m.setAddress("/mark6/show");
            m.addIntArg(0);
            sender.sendMessage(m);
			break;
		default:
			break;
	}
}
#endif


