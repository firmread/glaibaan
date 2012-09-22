/*
 *  Keys.cpp
 *  moviePlayer4_zaxis_psm
 *
 *  Created by psm on 3/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Keys.h"

Keys::Keys() {
}

bool[] Keys::keyPress() {
    if (key == CODED) {
		if (keyCode == LEFT) {
			keyleft = true;
		}
		if (keyCode == RIGHT) {
			keyright = true;
		}
		if (keyCode == UP) {
			keyup = true;
		}
		if (keyCode == DOWN) {
			keydown = true;
		}
    } 
    else {
		//for letter keys, use single quotes not double
		switch (key) {
				
			case '1':   //selection is a global in main, which movie to control
				selection = 1; //first rect
				break;
				
			case '2':
				selection = 2; //second rect
				break;
				
			case '3':   
				selection = 3; 
				break;
				
			case '4':
				selection = 4; 
				break;
				
			case 'd': // use as the "right" command
				keyright = true;
				break;
			case 'a':
				keyleft = true;
				break;
			case 'w': // "up"
				keyup = true;
				break;
			case 's':
				keydown = true;
				break;
		}
    }
    boolean keys[] = new boolean[4];
    keys[0]=keyleft; 
    keys[1]=keyup; 
    keys[2]=keyright;
    keys[3]=keydown;
    return keys;
    //println(keyright+" "+keyleft+" "+ keyup +" "+ keydown);
}

bool [] Keys::keyRelease() {
    if (key == CODED) {
		if (keyCode == LEFT) {
			keyleft = false;
		}
		if (keyCode == RIGHT) {
			keyright = false;
		}
		if (keyCode == UP) {
			keyup = false;
		}
		if (keyCode == DOWN) {
			keydown = false;
		}
    }
    else {
		switch (key) {
			case 'd': 
				keyright = false;
			case 'a':
				keyleft = false;
			case 'w':
				keyup = false;
			case 's':
				keydown = false;
		}
    }
    boolean keys[] = new boolean[4];
    keys[0]=keyleft; 
    keys[1]=keyup; 
    keys[2]=keyright;
    keys[3]= keydown;
    return keys;
}