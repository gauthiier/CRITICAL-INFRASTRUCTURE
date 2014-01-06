//
//  BarGraph.h
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#pragma once

#include "ofMain.h"
#include "AbstractGraph.h"

class BarGraph : public AbstractGraph
{
public:
    void setup();
    void update();
    void draw();
	virtual void addNewData(vector<int> newData);

	float barWidth;
	
	float col0[4];
	float col1[4];

};