//
//  GUI.h
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#pragma once

#include "ofMain.h"

class Camera : public ofEasyCam
{
public:
    void setup(int _camID);
    void update();
    void activate();
    void deactivate();
	
	int camID;

	ofNode lookAtNode;
	ofVec3f lookAtVec;

	ofVec3f positionVec;
	
	float distance;
	float rotSpeed;
	float swapProbability;
	float minSecondsBeforeSwapping;
	float timeBecameActive;
};