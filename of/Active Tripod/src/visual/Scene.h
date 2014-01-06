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

	BarGraph barGraph;
	
	float bgGradStartCol[4];
	float bgGradEndCol[4];

};