/*
 *  Scene.h
 *  moviePlayer1_withTUIO_A
 *
 *  Created by psm on 4/9/12.
 *  Copyright 2012 mackey DDA pratt. Very few rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "VidClip.h"
#include "Rotator.h"

#ifndef	RATE
#define	RATE 50.0 //how fast clip rect shifts to new loc, larger is slower //0925
#endif

class Scene : public ofBaseApp {

public:
	//constructor
	Scene(int _w, int _h, string _movfilename, string _textimgfilename, int _total, int _id);
	
	void	initDetail(string _videofile, float _xloc, float _yloc);
	void	setup();
	void	update();
	void	draw();
	void	updateLocation();
	void	setSelected(bool b);
	void	setTargetLocation (float _xt, float _yt);
	void	setTargetLocPct (float _px, float _py);  //as percentages of entire screen

	void	setRotation(bool _keyleft, bool _keyright, bool _keyup, bool _keydown) ;
	void	setRotation(float _angradians);  //second version of this for TUIO messages
	
	void	showAnimation();
	void	hideAnimation();
	void	pauseAnimationSoon();
	float   startedAnimTime;
    
	bool	isMoving;	//true when location is changing
    bool    wasMoving;  //to maintain selected state a bit of time after motion stops 0925
    bool	isSelected;
    
	float	YOFFSET, XOFFSET; //0.0 to 1.0  //pm1002
	float	targetX, targetY;
	
private:
	
	enum e_status {				//like a tiny little class, named "e_status"
		NOTHING, ANIMATION, TEXT  		//the possible values, use like custom variables
	} showingWhat;					//instance name used as "myStatus"  (all these terms are arbitrary, your choice)

	enum e_imgstate {				
		FADINGUP, OPAQUE, FADINGOUT, INVISIBLE  		
	} textImgState;	
	
	float	txtImgAlpha;
	float	getTxtImgAlpha();
	
	string	movFileNm, txtFileNm;
	
	ofImage	textImg;		
	
	VidClip	animationClip;	//controls the animating scene

	Rotator	rotMgr;
	
	bool	isVisible;
	
	float	thisX, thisY, thisZ, thisW, thisH;
	float	prevX, prevY;
	int		ID, total;
	
	float	thisAngle; //degrees
	float	WW,WH;
	
	float	startPretxtTime, TXTDELAY;  //wait for text to appear
    float   startStallTime, STALL;      //cover small pauses during translation
    
    float   startInactiveTime, INACTIVETIMEOUT;
    float   startSceneEndTime, SCENEENDTIMEOUT;
    
    bool    checkMotion(float _px, float _py);
    ofVec2f prevLoc;
    bool    isStill;
    
    int     matchcount, MAXMATCHES;
};