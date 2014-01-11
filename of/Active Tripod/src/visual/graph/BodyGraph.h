
#pragma once

#include "ofMain.h"
#include "AbstractGraph.h"

class testApp;

class BodyGraph : public AbstractGraph
{
public:
    void setup();
    virtual void update();
    virtual void draw();
	virtual void addNewData(vector<DataObject> newData);
	
	testApp *app;

	float barWidth;
	float lineWidth;

	bool isDrawBody;
	bool isDrawLines;
};