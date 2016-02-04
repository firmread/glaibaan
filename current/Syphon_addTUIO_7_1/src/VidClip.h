/*
 *  VidClip.h
 *  moviePlayer1big_withTUIO
 *
 *  Created by psm on 4/9/12.
 *  
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
    
    float       reloopPctTime;
    
    void        setFadeOut();
    void        setGhosted();
	
	float		clipAlpha;
	void		updateAlpha();
	enum e_alphastate {				
		FADINGUP, OPAQUE, FADETOGHOST, GHOSTED, FADINGOUT, INVISIBLE
	} alphaState;	
};