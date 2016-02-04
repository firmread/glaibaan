/*
 *  Keys.h
 *  moviePlayer4_zaxis_psm
 *
 *  Created by psm on 3/28/12.Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once



class Keys {
	
public:
	//constructor
	Keys();
	
	//methods
	bool	keyPress();
	bool	keyRelease();
	
	bool keyleft, keyright, keyup, keydown;
};