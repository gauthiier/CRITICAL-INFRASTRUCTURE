
#include "Camera.h"

void Camera::setup(int _camID)
{
	camID = _camID;
	lookAtNode.setPosition(0, 0, 0);
	setDistance(100);
	minSecondsBeforeSwapping = 2;
	isReadyForSwap = false;
}
	

void Camera::update()
{
	if (ofGetElapsedTimef() - timeBecameActive > minSecondsBeforeSwapping) 
		isReadyForSwap = true;

	positionVec.x = sin(ofGetElapsedTimef() * rotSpeed) * distance;
	//positionVec.y = 40;
	positionVec.z = cos(ofGetElapsedTimef() * rotSpeed) * distance;

	lookAtNode.setPosition(lookAtVec);
	setPosition(positionVec);
	lookAt(lookAtNode);
}


void Camera::activate()
{
	isReadyForSwap = false;
	timeBecameActive = ofGetElapsedTimef();
}


void Camera::deactivate()
{
	isReadyForSwap = false;
}