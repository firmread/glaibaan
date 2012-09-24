/*
 *  Rotator.h
 *  in moviePlayer4_zaxis_psm
 *
 *  Created by mackey DDA pratt on 3/28/12.
 * 
 *
 */

#pragma once
#include "Easer.h"

class Rotator {

private:	
	float	sDELTA;
	float	STOPACCURACY;
	float	thisAngle;
	float	rotationTarget;

	bool	isRotating;
	Easer	easer;
	
public:
	Rotator();
	void	setRotation(bool _leftkey, bool _rightkey);
	void	setRotation(float _angradians);
	//float	getRotation();
	float	updateRotation();
	void	setRotTarget(float _angle);
};