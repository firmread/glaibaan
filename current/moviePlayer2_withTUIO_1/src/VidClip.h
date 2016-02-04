/*
 *  VidClip.h
 *  moviePlayer1big_withTUIO
 *
 *  Created by psm on 4/9/12.
 *  Copyright 2012 pixelRiot. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"



class VidClip {
	
public:
	VidClip();
	
	void		init(string _movfilename, float _x, float _y);	//constructor
	
	ofVideoPlayer	clip;
	
	float			xloc, yloc;			//dont need?
	float			zlevel;
	float			xoffset, yoffset;	//permanent
	float			rotation;			//degrees //dont need?
	

	void		setup();
	void		update(float sceneZ);
	void		draw(float _zlevel);
	
	void		pause(float _zlevel);
	void		play();
	
	float		clipAlpha;
	void		updateAlpha();
	enum e_alphastate {				
		FADINGUP, OPAQUE, FADINGDOWN, GHOSTED  		
	} alphaState;	
};