//
//  gui->cpp
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#include "AbstractGraph.h"

float AbstractGraph::minGraphPercent;
float AbstractGraph::maxGraphPercent;

void AbstractGraph::setup()
{
	millisSinceLastPoint = 0;
}


void AbstractGraph::update()
{
	maxData = (ofGetWidth() * (AbstractGraph::maxGraphPercent - AbstractGraph::minGraphPercent)) /  graphItemXGap;
	normalisedTimeInc = ofMap(ofGetElapsedTimeMillis(), millisSinceLastPoint, millisSinceLastPoint + millisGap, 0, 1);
}


void AbstractGraph::draw()
{

}



void AbstractGraph::addNewData(vector<DataObject> newData)
{
	millisGap = ofGetElapsedTimeMillis() - millisSinceLastPoint;
	millisSinceLastPoint = ofGetElapsedTimeMillis();


	publisher0Data.push_back(newData[0]);
	publisher1Data.push_back(newData[1]);


	while (publisher0Data.size() > maxData && publisher0Data.size() > maxData)
	{
		publisher0Data.erase(publisher0Data.begin());
		publisher1Data.erase(publisher1Data.begin());
	}
}


void AbstractGraph::clear()
{
	publisher0Data.clear();
	publisher1Data.clear();
}