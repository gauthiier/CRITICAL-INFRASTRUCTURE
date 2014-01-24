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
	void clear();

	vector<DataObject> publisher0Data;
	vector<DataObject> publisher1Data;
	int maxData; // calculated from graphWidth and graphItemXGap
	
	static float minGraphPercent;
	static float maxGraphPercent;
	
	ofPoint currentPub0Point;
	ofPoint currentPub1Point;

	float graphItemXGap;
	
	float graphHeightMax;

	float col0[4];
	float col1[4];

	string graphName;
	float sendDataSpeed;


	float millisSinceLastPoint;
	float millisGap;
	//ofVec3f lastVecTarget0;
	//ofVec3f lastVecTarget1;
	float normalisedTimeInc;
	
	ofPoint endPoint0;
	ofPoint endPoint1;
	
	ofPoint graphTextPnt0;
	ofPoint graphTextPnt1;
	
	float animatedVal0;
	float animatedVal1;
	long long int animatedVal0LLI;
	long long int animatedVal1LLI;
};