//
//  AbstractGraph.h
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#pragma once

#include "ofMain.h"
#include "DataManager.h"

class AbstractGraph
{
public:
    void setup();
    virtual void update();
    virtual void draw();
	virtual void addNewData(vector<DataObject> newData);
	
	vector<DataObject> publisher0Data;
	vector<DataObject> publisher1Data;
	int maxData; // calculated from graphWidth and graphItemXGap
	
	static float minGraphPercent;
	static float maxGraphPercent;

	float graphItemXGap;
	
	float graphHeightMax;

	float col0[4];
	float col1[4];

};