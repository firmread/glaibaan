/*
 *  Scene.h
 *  moviePlayer1big_withTUIO
 *
 *  Created by psm on 4/9/12.
 *  Copyright 2012 mackey DDA pratt. Very few rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "Detail.h"
#include "Rotator.h"

#ifndef	RATE
#define	RATE 5.0 //how fast clip rect shifts to new loc, larger is slower
#endif

class Scene : public ofBaseApp {

public:
	//constructor
	Scene(int _x, int _y, int _w, int _h, string _BGfilename, int _total, int _id);
	void	initDetail(string _videofile, float _xloc, float _yloc);
	void	setup();
	void	update();
	void	draw();
	void	updateLocation();
	void	setSelected(bool b);
	void	setTargetLocation (float _xt, float _yt);
	void	setTargetLocPct (float _px, float _py);  //as percentages of entire screen

	void	setRotation(bool _keyleft, bool _keyright, bool _keyup, bool _keydown) ;
	void	setRotation(float _angradians);  //second version of this
	
	void	show();
	void	hide();
	

	
private:
	vector<Detail>	theDetails;		//array

	int		numOfDetails;
	ofImage	panorama;
	Rotator	rotMgr;
	
	bool	isSelected;
	bool	isVisible;
	
	float	thisX, thisY, thisZ, thisW, thisH;
	float	prevX, prevY;
	int		ID, total;
	float	targetX, targetY;
	bool	isMoving;	//true when location is changing
	
	float	ROT; //degrees
	float	yOffsetPct;
};