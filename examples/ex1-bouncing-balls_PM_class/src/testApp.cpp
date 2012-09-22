/*
 *  testApp.cpp
 *  bouncing demo (simple demo, Newton won't be happy)
 *
 *  by Rick Companje
 *  modified to use a Class by mackey DDA pratt
 */
 
#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
	
	for (int i=0; i<NUM; i++) { 	
		
		theBouncers[i] = new Bouncer(i);
	}
	
	//white background and max 60fps
	ofBackground(255,255,255);
	ofSetFrameRate(60);
	
	ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void testApp::update() {
	for (int i=0; i<NUM; i++) {
		
		theBouncers[i] -> update();
	}	
}

//--------------------------------------------------------------
void testApp::draw() {
	
	
	
	//ofEnableAlphaBlending();			// turn on alpha blending
	ofSetColor(255,255,255,127);		// 50% transparent
	
	ofRect(0,0,ofGetWidth(),ofGetHeight());
	
	//draw
	for (int i=0; i<NUM; i++) {
		theBouncers[i] -> draw();
	}
	//ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

