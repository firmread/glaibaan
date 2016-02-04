/*
 *  Rotator.h
 *  in moviePlayer4_zaxis_psm
 *
 *  Created by mackey DDA pratt on 3/28/12.
 * 
 *
 */

#pragma once


class Rotator {

private:	
	float	sDELTA;
	float	STOPACCURACY;
	float	thisAngle;
	float	rotationTarget;

	bool	isRotating;
	
	float	swingTo (float aRotEnd, float aRotStart);
	
public:
	Rotator();
	void	setRotation(bool _leftkey, bool _rightkey);
	//float	getRotation();
	float	updateRotation();
	void	setRotTarget(float _angle);


//from TUIO events via testApp
	void	setRotation(float _angradians);
    
    float catchUpSpeed;


};