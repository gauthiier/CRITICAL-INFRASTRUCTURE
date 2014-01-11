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
	printf("AbstractGraph::setup()\n");
}


void AbstractGraph::update()
{
	maxData = (ofGetWidth() * (AbstractGraph::maxGraphPercent - AbstractGraph::minGraphPercent)) /  graphItemXGap;
	printf("ofGetWidth():%i, maxData:%i, graphItemXGap:%f, screen active:%f \n", ofGetWidth(), maxData, graphItemXGap, (AbstractGraph::maxGraphPercent - AbstractGraph::minGraphPercent));
}


void AbstractGraph::draw()
{

}


void AbstractGraph::addNewData(vector<DataObject> newData)
{
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