
#pragma once

#include "ofMain.h"
#include "DataManager.h"

class testApp;

class Graph
{
public:
	Graph(int _graphID);
    void update(ofVec3f ativeCamPos);
	void draw();
	void addNewData(DataObject newData);
	ofMesh getMesh(vector<DataObject> publisherData, float* col);
	void createInfoTextFbo();
	void clear();

	testApp *app;
	int graphID;

	vector<DataObject> publisher0Data;
	int maxData; // calculated from graphWidth and graphItemXGap
	
	ofFbo infoTextFbo;

	static float minGraphPercent;
	static float maxGraphPercent;
	static float maxGraphWidth;
	static bool isDrawLines;
	static float graphItemXGap;
	static float lineWidth;
	static float graphHeightMax;
	static float graphEndPercent;
	
	//float minGraphPercent;
	//float maxGraphPercent;
	//float maxGraphWidth;
	//bool isDrawLines;
	//float graphItemXGap;
	//float lineWidth;
	//float graphHeightMax;
	//float graphEndPercent;
	
	ofPoint currentPub0Point;

	float col0[4];


	float distToCam;
	ofVec3f centre;
};