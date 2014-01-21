//
//  GUI.h
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#pragma once

#include "ofMain.h"
#include "Graph.h"
#include "DataManager.h"
#include "GraphManager.h"
#include "ofxFTGL.h"
#include "Camera.h"

class testApp;

class Scene
{
public:
    void setup();
	void setupTitleFbo();
    void update();
    void draw();
	void setViewport();
	void drawTextBox(string copy, string align);
	void addNewData(int i, DataObject newData);
	void clearGraphData();
	void keyPressed(int key);
	void switchCamera();

	GraphManager graphManager;
	
	Camera cameras[3];
	Camera *activeCamera;
	ofNode lookAtNode;
	ofVec3f lookAtVec;

	ofRectangle viewport;
	
	ofxFTGLSimpleLayout text;
	ofxFTGLSimpleLayout thinText;
	ofFbo titleFbo;
	ofImage targetImage;
	float titleScale;

	float legendTextSize;
	float legendTextSpacing;
	float legendTextLineLength;
	ofPoint legendTextPoint;
	
	float gridScale;
	float gridTicks;
	float gridCol[4];

	bool isCamRotate;
	bool isCamAutoSwap;
};