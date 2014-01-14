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
#include "ofxFTGL.h"
#include "GraphManager.h"

class testApp;

class Scene
{
public:
    void setup();
    void update();
    void draw();
	void setViewport();
	void drawTextBox(string copy, string align);
	void addNewData(vector<DataObject> newData);
	void clearGraphData();
	void keyPressed(int key);


	GraphManager graphManager;

	ofEasyCam camera;
	ofRectangle viewport;

	ofxFTGLSimpleLayout text;

};