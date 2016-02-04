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
#define	RATE 5.0 //how fast clip rect shifts to new loc, larger is slower
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
    
	bool	isMoving;	//true when location is changing
    bool	isSelected;
	
private:
	
	enum e_status {				//like a tiny little class, named "e_status"
		NOTHING, ANIMATION, TEXT  		//the possible values, use like custom variables
	} showingWhat;					//instance name used as "myStatus"  (all these terms are arbitrary, your choice)

	enum e_imgstate {				
		FADINGUP, OPAQUE, FADINGDOWN, INVISIBLE  		
	} imageState;	
	
	float	imgAlpha;
	float	getImgAlpha();
	
	string	movFileNm, txtFileNm;
	
	ofImage	textImg;		
	
	VidClip	animationClip;	//controls the animating scene

	Rotator	rotMgr;
	
	bool	isVisible;
	
	float	thisX, thisY, thisZ, thisW, thisH;
	float	prevX, prevY;
	int		ID, total;
	float	targetX, targetY;
	
	float	thisAngle; //degrees
	float	yOffsetPct;
	float	WW,WH;
	
	float	startPauseTime, PAUSEDELAY;
};