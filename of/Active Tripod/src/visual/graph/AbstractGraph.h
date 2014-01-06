//
//  AbstractGraph.h
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#pragma once

#include "ofMain.h"

class AbstractGraph
{
public:
    void setup();
    void update();
    void draw();
	virtual void addNewData(vector<int> newData);
	
	vector<int> publisher0Data;
	vector<int> publisher1Data;
	int maxData; // calculated from graphWidth and graphItemXGap

	float graphItemXGap;
	ofPoint startPnt;
	int graphWidth;
	int graphHeight;

};