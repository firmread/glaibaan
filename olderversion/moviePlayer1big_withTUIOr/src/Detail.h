/*
 *  Detail.h
 *  moviePlayer1big_withTUIO
 *
 *  Created by psm on 4/9/12.
 *  Copyright 2012 pixelRiot. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"



class Detail {
	
public:
	ofImage			stillimg;			//not using
	ofVideoPlayer	animation;
	
	float			xloc, yloc;			//dont need?
	float			zlevel;
	float			xoffset, yoffset;	//permanent
	float			rotation;			//degrees //dont need?
	
	Detail();	//constructor
	void		initYourself(string _videofile, float _x, float _y);
	void		setup();
	void		update(float sceneX, float sceneY, float sceneZ);
	void		draw(float _zlevel);
};