

#pragma once

#include "ofMain.h"
#include "BarGraph.h"
#include "BodyGraph.h"
#include "SeparateBodyGraph.h"
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
	void drawGraphValues();
	void drawCrosshairs();
	void drawHUDBG();
	void drawHUDCopy();
	void drawHUDColourBars();
	void drawTextBox(string copy, string align);
	void addNewData(vector<DataObject> newData);
	void clearGraphData();
	void keyPressed(int key);
	string addCommasToNumberString(string num);
	string reduceDecimalCount(string num, int maxDecimal);
	
	BarGraph barGraph;
	BodyGraph bodyGraph;
	SeparateBodyGraph separateBodyGraph;

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
	float videoWidthPercentage;
	float videoHeightPercentage;
	bool isVideoVisible;
	bool isImageVisible;

	// graph text
	float graphTextColour[4];
	float graphTextSize;

	// crosshairs
	float crosshairLineWidth;
	float crosshairAlpha;
	float crosshairCircleSize;
	float crosshairVertScale;
	float crosshairHorizScale;

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
	float averageAmount;

	bool isClearOnNewMinMax;

	// text colour boxes
	float topColourBoxXOffset;
	float bottomColourBoxXOffset;
	float colourBoxThickness;
	
	float valDecimalPoints0;
	float valDecimalPoints1;
};