
#pragma once

#include "ofMain.h"
#include "AbstractGraph.h"

class testApp;

class SeparateBodyGraph : public AbstractGraph
{
public:
    void setup();
    virtual void update();
    virtual void draw();
	virtual void addNewData(vector<DataObject> newData);
	ofMesh getMesh(vector<DataObject> publisherData, float* col, int graphID);

	testApp *app;

	float lineWidth;

	bool isDrawLines;
	float graphEndPercent;
};