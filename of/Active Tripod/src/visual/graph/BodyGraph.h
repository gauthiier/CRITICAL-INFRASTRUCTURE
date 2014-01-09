
#pragma once

#include "ofMain.h"
#include "AbstractGraph.h"

class BodyGraph : public AbstractGraph
{
public:
    void setup();
    virtual void update();
    virtual void draw();
	virtual void addNewData(vector<DataObject> newData);

	float barWidth;
	float lineWidth;

	float col0[4];
	float col1[4];
};