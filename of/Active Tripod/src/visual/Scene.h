//
//  GUI.h
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#pragma once

#include "ofMain.h"
#include "BarGraph.h"
#include "BodyGraph.h"
#include "DataManager.h"
#include "ofxFTGL.h"

class testApp;

class Scene
{
public:
    void setup();
    void update();
    void draw();
	void drawVideo();
	void drawHUDBG();
	void drawHUDCopy();
	void drawHUDColourBars();
	void drawTextBox(string copy, string align);
	void addNewData(vector<DataObject> newData);
	void keyPressed(int key);
	
	BarGraph barGraph;
	BodyGraph bodyGraph;
	ofShader rgbShader;
	ofVideoGrabber vidGrabber;
	ofImage bgImg;
	ofxFTGLSimpleLayout text;

	AbstractGraph* activeGraph;



	// video image vars
	float brightness;
	float contrast;
	float saturation;
	float red;
	float green;
	float blue;
	float alpha;
	bool isVideoVisible;
	bool isImageVisible;
	
	// HUD background vars
	float hudColour[4];
	float circlePointSize;
	float hudHoleWidthPercentage;
	float hudHoleHeightPercentage;

	// text vars
	float xMargin;
	float yMargin;
	float yMarginBottomOffset;
	float lineLength;
	float lineSpacing;
	float textSize;
	float textColour[4];
	string tlStr;
	string trStr;
	string blStr;
	string brStr;
	long millisAtLastData;
	float averageAmount;

	// text colour boxes
	float topColourBoxXOffset;
	float bottomColourBoxXOffset;
	float colourBoxThickness;
};