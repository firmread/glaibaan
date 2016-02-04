/*
 *  Scene.cpp
 *  moviePlayer1_withTUIO_A
 *
 *  Created by mackey DDA pratt on 4/9/12.
 *	Mod Sep2012
 *
 *  Container object for a background animation and the secret text image that appears when fiducial disappears
 *
 */

#include "Scene.h"

Scene::Scene(int _w, int _h, string _movfilename, string _textimgfilename, int _total, int _id) {
		
	yOffsetPct = 0.0; //not used
	
	movFileNm  = _movfilename;
	txtFileNm = _textimgfilename;
	
	WW = float(ofGetWidth());
	WH = float(ofGetHeight());
	
	ID =  _id;
    targetX = thisX = _w/-2.0; //_x; //center offset
    targetY = thisY = _h/-2.0; //_y;
	
	thisZ = _id;			   //just to start
	total = _total;			   //numofscenes
	
    thisW = _w;				   //not using?
    thisH = _h;
	thisAngle = 0;			   //rotation, degrees
	
	isMoving = false;
    isSelected = false;
	isVisible = false;			//eventually, all will be hidden unless the related indicia stamp is present	
	
	PAUSEDELAY = 2.0;			//seconds until text appears after "unselected" (fiducial disappears)
	startPauseTime = 0.0f;		//gets set by pauseAnimationSoon()
	showingWhat = NOTHING;		//other possible values ANIMATION TEXT
	
	imageState = INVISIBLE;		//other possible values FADINGUP, OPAQUE, FADINGDOWN
	
}


//main method calls...

void Scene::setup() {
	
	animationClip.init(movFileNm, thisX, thisY);
	textImg.loadImage(txtFileNm);	//openFrameworks happier not doing this in constructor!
	
	animationClip.setup();
}

void Scene::update() {
	
	if (showingWhat!=NOTHING) {
		animationClip.update(thisZ);
		updateLocation();		//has to happen even if not selected, in case video is still moving when another one is selected
	}
	//decide to show test image after a delay
	if (showingWhat==ANIMATION) {
		if ((startPauseTime>0)&&((ofGetElapsedTimef()-startPauseTime)>PAUSEDELAY)) { 
			//if (showingWhat==ANIMATION) imageState=FADINGUP;
			imageState=FADINGUP;
			showingWhat=TEXT;
			//printf("showingWhat=%i imageState=%i\n",showingWhat,imageState);
            
            //AND THEN, what? after a time delay show nothing?
		}
	}
}

void Scene::draw() {
    
	if (showingWhat!=NOTHING) {
		float temp;
		
		
		
		ofPushMatrix();
		
		ofTranslate(thisX, thisY, thisZ);
		ofRotate(thisAngle);					//wants degrees
		
		switch (showingWhat) {
				
			case ANIMATION:
                //ofSetColor(255,255,255);
				animationClip.draw(thisZ);     //the VidClip object handles the x.y

				if (imageState!=INVISIBLE) {
					//also keep drawing text in case it needs to fade out
					ofPushMatrix();				
						ofTranslate(0,0,thisZ+1); //put text "on top"
						ofEnableAlphaBlending();
							ofSetColor(255,255,255,getImgAlpha());
							textImg.setAnchorPercent(0.5f,0.5f);//center! float xPct, float yPct
							textImg.draw(0, 0);	
						ofDisableAlphaBlending();
					ofPopMatrix();
				}
				break;
				
			case TEXT:
				
				//ofSetColor(255,255,255,125); //125 = 50% alpha
				animationClip.pause(thisZ);  //includes simple tint-blending, for transparency
                
				ofPushMatrix();				
					ofTranslate(0,0,thisZ+1); //put text "on top"
					ofEnableAlphaBlending();
						ofSetColor(255,255,255,getImgAlpha());
						textImg.setAnchorPercent(0.5f,0.5f);//center! float xPct, float yPct
						textImg.draw(0, 0);	
					ofDisableAlphaBlending();
 				ofPopMatrix();
                
				break;

			default:
				break;
		}
		
		ofPopMatrix();
	}
}

float Scene::getImgAlpha() { //call in the draw loop always
	//global! float imgAlpha;

	switch (imageState) {
			
		case OPAQUE :
			imgAlpha = 255.0f;
			break;
			
		case INVISIBLE :
			imgAlpha = 0.0f;
			break;
			
		case FADINGUP:
			//should be fading-in, so add to the opacity
			imgAlpha += 1.0f;      //<--EDIT to change speed of fade
			if (imgAlpha >= 255.0f) {
				imageState=OPAQUE;
				imgAlpha = 255.0f;
			} 
			break;
			
		case FADINGDOWN :
			//should be fading out, so reduce the opacity
			imgAlpha -= 5.0f;     //<--EDIT to change speed of fade
			if (imgAlpha <= 0.0f) {
				imageState=INVISIBLE;
				imgAlpha = 0.0f;
			} 
			break;
	}
	return imgAlpha;
}

//called from events in testApp --------------------------------------------------

void Scene::showAnimation() {  //from TUIOadded or mousePressed

	showingWhat=ANIMATION;								//video plays...
	if (imageState!=INVISIBLE) imageState=FADINGDOWN;	//...and text fades out if there
	
	startPauseTime=0; //dont timeout into hide()
	animationClip.play();  //may be paused
	cout << "Scene "<<ID<<" is visible."<<endl;
}
void Scene::pauseAnimationSoon() {  //from TUIORemoved or mouseReleased
	//start a timer to delay onset of hiding (sometimes we lose the fiducial for a moment)
	startPauseTime = ofGetElapsedTimef();
	//printf("startPauseTime=%f \n",startPauseTime);
}

//called when selection changes in main by keyReleased handler OR tuioUpdated()
void Scene::setSelected(bool b) {	
    isSelected = b;
	//move to front if this is selected
	if (isSelected) {
		thisZ = total+1;
        printf("-> selected Scene # %i\n",ID);
	} else {
		thisZ = ID;
        printf("-> UN-selected Scene # %i\n",ID);
	}
    //WIP! make an on-screen report of all scenes and which are "selected"
}

//from TUIOupdated or mouseDragged/arrow keys
void Scene::setTargetLocPct (float _px, float _py) { //as percentages of entire screen
    isMoving = true;
    targetX = WW*_px; //WW is screen width, WH is screen height
    targetY = (WH*_py)-(WH*yOffsetPct); //crude calibration
	printf("Scene %i target set. Selected=%i \n", ID, (isSelected==true) ? 1:0 );
           //to x=%f y=%f \n",ID,targetX,targetY);
}
//...only from TUIOupdated
void Scene::setRotation(float _angradians) { //range is 0.0 to 6.28 radians at 360°
    rotMgr.setRotation(_angradians);
	rotMgr.updateRotation();
}
//...only from keyReleased handler, sent to the selected scene...
void Scene::setRotation(bool _keyleft, bool _keyright, bool _keyup, bool _keydown) { //will be {keyleft,keyup,keyright,keydown} booleans
    rotMgr.setRotation(_keyleft,_keyright);
	rotMgr.updateRotation();
}
//----------------------------------------------------------------------------------


void Scene::updateLocation() { //automatic translation to clicked or target location
	
	thisAngle = rotMgr.updateRotation(); 
	
	if (isMoving) {
		
		float xDiff = (targetX-thisX);
		float yDiff = (targetY-thisY);
		float xShift = xDiff/RATE;
		thisX = thisX + xShift;
		float yShift = yDiff/RATE;
		thisY = thisY + yShift;
		
		if (abs(yDiff+xDiff) < 4.0) { //dont make this too sensitive, it creates an apparent delay
			thisX = targetX; 
			thisY = targetY;
			
			isMoving = false;
			//cout << "stopped moving" << endl;
		}
    }
    prevX = thisX; 
    prevY = thisY;
}



//=================================================================
