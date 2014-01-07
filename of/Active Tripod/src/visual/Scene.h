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

class testApp;

class Scene
{
public:
    void setup();
    void update();
    void draw();
	void drawVideo();
	void drawHUD();

	BarGraph barGraph;
	ofShader rgbShader;
	ofImage bgImg;
	
	float brightness, contrast, saturation, red, green, blue, alpha;
	
	float hudColour[4];
	float circlePointSize;
	float radiusW;
	float radiusH;
};