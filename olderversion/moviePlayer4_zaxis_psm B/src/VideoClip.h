/*
 *  videoClip.h
 *  in moviePlayer_zaxis_psm
 *
 *  Created by mackey DDA pratt on 3/28/12.
 *
 */
#pragma once

#include "Rotator.h"
#include "ofVideoPlayer.h"

#ifndef RATE
#define RATE 5.0 //how fast clip rect shifts to new loc, larger is slower
#endif

//no!! class VideoClip : public testApp {
class VideoClip : public ofBaseApp {
	
private:
	
	bool	isPlaying;
	bool	isSelected; 
	bool	isVisible;
	
	float	thisX, thisY, thisZ, thisW, thisH;
	float	prevX, prevY;
	int		ID, total;
	float	targetX, targetY;
	bool	isMoving; //true when location is changing
	
	float	ROT; //, prevROT;
	
	ofVideoPlayer thisMovie;
	
	Rotator rotMgr;
	
	// methods
	
	void	grab();
	void	updateMovie(int _id);

	int		getID();
	float	getPrevRot();
	
	void	updateRotation();
	void	updateLocation();
	bool	updateState(bool _over);
	
	void	playThisVideo();
	void	pauseThisVideo();
	//void	cleanup();
	
	public:
	void	update();
	void	draw();
	void	setSelected(bool b);
	void	setRotation(bool, bool, bool ,bool);
	void	setTargetLocation (float _xt, float _yt);
	// constructors
	VideoClip();
	VideoClip(int _x, int _y, int _w, int _h, string _file ,int _total, int _id);
	
};
