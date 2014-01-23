
#pragma once

#include "ofMain.h"
#include "DataManager.h"
#include "ofxFTGL.h"

class testApp;

class Graph
{
public:
	Graph(int _graphID);
    void update(ofVec3f ativeCamPos);
	void draw();
	void drawGraphBody();
	void drawGraphText();
	void addNewData(DataObject newData);
	void setFboSettings();
	void drawInfoToFbo();
	void clear();
	vector<string> explode(const string &delimiter, const string &str);
	bool hasColorChanged();
	void updateColours();

	testApp *app;
	int graphID;

	int maxData; // calculated from graphWidth and graphItemXGap
	
	ofFbo infoTextFbo;
	ofFbo::Settings settings;
	ofxFTGLSimpleLayout* text;
	bool isInfoTextSet;

	static float maxGraphWidth;
	static bool isDrawBody;
	static bool isDrawLines;
	static bool isClampYValues;
	static float graphItemXGap;
	static float lineThickness;
	static float graphHeightMax;
	static float graphEndPercent;
	static float zRange;
	static float graphTextZOffset;
	static float colFront[4];
	static float colBack[4];
	static float prevColFront[4];
	static float prevColBack[4];
	
	static float lineLength;
	static float lineSpacing;
	static float textSize;
	static float fboW;
	static float fboH;
	static float textY;
	static ofPoint textPnt;
	static bool isAnimating;
	static bool isClearOnNewMinMax;
	
	float col0[4];


	float distToCam;
	ofVec3f centre;

	string info;

	ofMesh graphMesh;
	float currentValue;
	float currentMin;
	float currentMax;
	
	float millisSinceLastPoint;
	float millisGap;
	ofVec3f lastVecTarget;
};