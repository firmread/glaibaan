/*
 *  Scene.cpp
 *  moviePlayer1_withTUIO_A
 *
 *  Created by mackey DDA pratt on 4/9/12.
 *	Mod Sep2012
 *
 *  Container object for a background animation and the secret text image that appears when fiducial disappears
 *  WIP 
    ...who's in front?  
    ...age-out the text overlay
    ...if card present but not moving, age out the animation
 */

#include "Scene.h"

Scene::Scene(int _w, int _h, string _movfilename, string _textimgfilename, int _total, int _id) {
		
	YOFFSET = 0.00; //WIP percentage to shift "center" of card relative to animation
	XOFFSET = 0.00; //pm1002
	
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
	
	isMoving = false;          //only true when receving change data from TUIO, but that is erratic
    wasMoving = false;
    isSelected = false;
	isVisible = false;		   //eventually, all will be hidden unless the related indicia stamp is present
    isStill = false;           //to determine if a card has been abandoned
    prevLoc = ofVec2f(0,0);
    
    STALL = 1.5;               //secs before deciding fiducial has really stopped moving, for z-level assignment
	startStallTime = 0.0f;
    
	TXTDELAY = 2.0;			   //seconds until text appears after "unselected" (fiducial disappears)
	startPretxtTime = 0.0f;		//gets set by pauseAnimationSoon()
	showingWhat = NOTHING;		//other possible values ANIMATION TEXT
	
	textImgState = INVISIBLE;	//other possible values FADINGUP, OPAQUE,FADETOGHOST, GHOSTED, FADINGOUT
	
    startInactiveTime = 0.0f;
    INACTIVETIMEOUT = 10.0f; //secs <--EDIT! how long to wait showing text after fiducial is gone
    
    matchcount=0;
    MAXMATCHES=200; //higher takes longer to call it "still"
    startSceneEndTime=0.0f;
    SCENEENDTIMEOUT = 60.0f; //<--EDIT! secs before nonmoving card's animation disappears
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
        
//        if (checkMotion(thisX, thisY)) {
//            //if the card hasn't been moved in a while, remove the animation
//            if ((startSceneEndTime>0)&&((ofGetElapsedTimef()-startSceneEndTime)>SCENEENDTIMEOUT)) {
//                animationClip.setFadeOut();
//                startSceneEndTime=0;
//                matchcount=0;
//                printf("end scene fadeout started");
//            }
//        }
        
        //should we show the text?
		if ((startPretxtTime>0)&&((ofGetElapsedTimef()-startPretxtTime)>TXTDELAY)) {
            //yes!
			animationClip.setGhosted();  //0928
            animationClip.pause(thisZ);
			textImgState=FADINGUP;
			showingWhat=TEXT;
			printf("Text delay reached, showingWhat=%i textImgState=%i\n",showingWhat,textImgState);
            //AND THEN, after a time delay fade text+animation (if card stays gone)
            startInactiveTime = ofGetElapsedTimef();  //0929
		}
 	}
    
    if (showingWhat==TEXT) {  //WIP 0928  this delay should probably be longer
        if (textImgState==OPAQUE) { 
            if (ofGetElapsedTimef()>(startInactiveTime+INACTIVETIMEOUT)) {
                printf("Inactive Timeout reached for Scene %i\n",ID);
                //printf("...with showingWhat=%i textImgState=%i\n",showingWhat,textImgState);
                
                //fade out video and text to invisible...
                animationClip.setFadeOut();
                textImgState=FADINGOUT;
            }        
        }
    }
}

void Scene::draw() {
    
	if (showingWhat!=NOTHING) {
		float temp;
		
		ofPushMatrix();
        //map draw dimension to match real postcard position
        // red dot version
//        float drawX = ofMap(thisX, 20, 620, 120, 520);
        // postcard version
//        float drawX = ofMap(thisX, 102, 422, -18, 488);        
//		float drawY = ofMap(thisY, 177, 370, 174, 347);
//        ofTranslate(drawX, drawY, thisZ);
        
        
		ofTranslate(thisX, thisY, thisZ);
		ofRotate(thisAngle);//wants degrees
		//ofScale(0.5,0.5);
        
		switch (showingWhat) {
				 
			case ANIMATION:
                //ofSetColor(255,255,255);
				animationClip.draw(thisZ);     //the VidClip object handles the x.y

				if (textImgState!=INVISIBLE) {
					//also keep drawing text in case it needs to fade out
					ofPushMatrix();				
						ofTranslate(0,0,thisZ+1); //put text "on top"
						ofEnableAlphaBlending();
							ofSetColor(255,255,255,getTxtImgAlpha());
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
						ofSetColor(255,255,255,getTxtImgAlpha());
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

float Scene::getTxtImgAlpha() { //call in the draw loop - returns and sets
	switch (textImgState) {
			
		case OPAQUE:
			txtImgAlpha = 255.0f;
			break;
			
		case INVISIBLE:
			txtImgAlpha = 0.0f;
			break;
			
		case FADINGUP:
			//should be fading-in, so add to the opacity
			txtImgAlpha += 1.0f;      //<--EDIT to change speed of fade
			if (txtImgAlpha >= 255.0f) {
				textImgState=OPAQUE;
				txtImgAlpha = 255.0f;
			} 
			break;
			
		case FADINGOUT:
			//should be fading out, so reduce the opacity
			txtImgAlpha -= 1.0f;     //<--EDIT to change speed of fade
            //printf("txtImgAlpha=%f\n",txtImgAlpha);
			if (txtImgAlpha <= 0.0f) {
				textImgState=INVISIBLE;
				txtImgAlpha = 0.0f;
			} 
			break;
	}
	return txtImgAlpha;
}

//called when selection changes in main by number keys keyReleased handler OR setPriority in main update()
void Scene::setSelected(bool b) {	
    isSelected = b;
	//move to front if this is selected
	if (isSelected) {
		thisZ = total+1;
        //printf("-> selected Scene # %i with startTime= %f\n",ID, startedAnimTime);
	} else {
		thisZ = ID;
        //printf("-> UN-selected Scene # %i\n",ID);
	}
    //notice the on-screen report of all scenes and which are "selected"
}

//called from events in testApp --------------------------------------------------

void Scene::showAnimation() {  //***fiducial first detected, from TUIOadded or mousePressed

	showingWhat=ANIMATION;								//video plays...
	if (textImgState!=INVISIBLE) textImgState=FADINGOUT;	//...and text fades out if there
	startedAnimTime=ofGetElapsedTimef(); //helps determine who should be on top
	startPretxtTime=0; //dont timeout into ghosting
    startSceneEndTime=0; //pm1002 dont timeout into fadingout
	animationClip.play();  //may be paused
	cout << "Scene "<<ID<<" is visible."<<endl;
}

void Scene::pauseAnimationSoon() {  //*** from TUIORemoved or mouseReleased
	//start a timer to delay onset of hiding (sometimes we lose the fiducial for a moment)
	startPretxtTime = ofGetElapsedTimef();
	//printf("startPretxtTime=%f \n",startPretxtTime);
}


//from TUIOupdated or mouseDragged/arrow keys
void Scene::setTargetLocPct (float _px, float _py) { //*** as percentages of entire screen
    isMoving = true;
    //for age test (to determine frontmost) (also storing a start time stamp)
    
	//WW is screen width, WH is screen height; target is raw TUIO location data
	//WIP //pm1002
    targetX = (WW*_px)-(WW*XOFFSET); 
	
    targetY = (WH*_py)-(WH*YOFFSET); 
	
	//printf("Scene %i target set. Selected=%i \n", ID, (isSelected==true) ? 1:0 );
           //to x=%f y=%f \n",ID,targetX,targetY);
}

//...only from TUIOupdated
void Scene::setRotation(float _angradians) { //*** range is 0.0 to 6.28 radians at 360°
    rotMgr.setRotation(_angradians);
	rotMgr.updateRotation();
}

//...only from keyReleased handler, sent to the selected scene...
void Scene::setRotation(bool _keyleft, bool _keyright, bool _keyup, bool _keydown) { //will be {keyleft,keyup,keyright,keydown} booleans
    rotMgr.setRotation(_keyleft,_keyright);
	rotMgr.updateRotation();
}

//----------------------------------------------------------------------------------
bool Scene::checkMotion(float _px, float _py) {  //0928
            
        //compare previous vertices to latest ones
        ofVec2f newloc = ofVec2f(_px,_py);
        bool result;
        result = newloc.match(prevLoc,0.05f); //<--EDIT tolerance for being still
        prevLoc = ofVec2f(_px,_py);
    
        if (result==true) {
            //count how many time this happens within a time period
            matchcount++;
            printf("matchcount=%i\n",matchcount);
        } else {
            if (matchcount>0) matchcount--;
            startSceneEndTime=0; //stop the countdown
            printf("restarting-------\n");
        }
        
        if (matchcount>MAXMATCHES) { //how many matches will trigger a countdown to fadeout
            if (startSceneEndTime==0) {
                matchcount=0;
                startSceneEndTime = ofGetElapsedTimef(); //start the countdown
                printf("match countdown started------------");
            }
            return true;
        } else {
            return false;
        }
        
}
//----------------------------------------------------------------------------------

//always called in update() if showingWhat!=NOTHING
void Scene::updateLocation() { //automatic translation to clicked or target location
	
	thisAngle = rotMgr.updateRotation(); 
	
	if (isMoving) {


        
        
		float xDiff = (targetX-thisX);  //WIP idea, use x&yDiff to decide "if really moving"
		float yDiff = (targetY-thisY);
		float xShift = xDiff/RATE;
		thisX = thisX + xShift;
		float yShift = yDiff/RATE;
		thisY = thisY + yShift;
		
		if (abs(yDiff+xDiff) < 4.0) { //dont make this too sensitive, it creates an apparent delay
            float catchUp = 0.01f;
            
            thisX = catchUp * targetX + (1-catchUp) *thisX;
            thisY = catchUp * targetY + (1-catchUp) *thisY;
            
//            thisX = targetX; 
//			thisY = targetY;
			
			isMoving = false;
            startStallTime = ofGetElapsedTimef();
            wasMoving = true;
			//cout << "stopped moving" << endl;
		}
    }
    prevX = thisX; 
    prevY = thisY;
    
    if (wasMoving) {
        if ((ofGetElapsedTimef()-startStallTime)>STALL) {
            wasMoving = false;      //WIP 0925 needs testing
        }
    } //see setPriority() in testapp
}



//=================================================================
