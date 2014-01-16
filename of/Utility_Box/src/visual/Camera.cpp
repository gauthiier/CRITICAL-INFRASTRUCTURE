
#include "Camera.h"

void Camera::setup(int _camID)
{
	camID = _camID;
	lookAtNode.setPosition(0, 0, 0);
	setDistance(100);
}
	

void Camera::update()
{
	positionVec.x = sin(ofGetElapsedTimef() * rotSpeed) * distance;
	//positionVec.y = 40;
	positionVec.z = cos(ofGetElapsedTimef() * rotSpeed) * distance;

	lookAtNode.setPosition(lookAtVec);
	setPosition(positionVec);
	lookAt(lookAtNode);
}