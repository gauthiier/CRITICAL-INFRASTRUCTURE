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

}


void AbstractGraph::draw()
{

}


void AbstractGraph::addNewData(vector<DataObject> newData)
{
	publisher0Data.push_back(newData[0]);
	publisher1Data.push_back(newData[1]);

	maxData = (ofGetWidth() / graphItemXGap) * (AbstractGraph::maxGraphPercent - AbstractGraph::minGraphPercent);

	while (publisher0Data.size() > maxData && publisher0Data.size() > maxData)
	{
		publisher0Data.erase(publisher0Data.begin());
		publisher1Data.erase(publisher1Data.begin());
	}
}