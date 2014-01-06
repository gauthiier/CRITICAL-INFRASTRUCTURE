//
//  gui->cpp
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#include "BarGraph.h"


void BarGraph::setup()
{
	AbstractGraph::setup();

	graphItemXGap = 10;
}


void BarGraph::update()
{
//	if (ofGetFrameNum() % 30 == 0)
//		printf("publisher0Data.size():%i \n", publisher0Data.size());
}


void BarGraph::draw()
{
	if (publisher0Data.size() > 1)
	{
		for (int i = 0; i < publisher0Data.size() - 1; i++)
		{
			if (i < publisher0Data.size() - 2)
			{
				ofPushStyle();
				ofSetColor(0, 0, 0);
				ofLine(i * graphItemXGap, publisher0Data[i], (i + 1) * graphItemXGap, publisher0Data[i + 1]);
				ofSetColor(0, 0, 0);
				ofLine(i * graphItemXGap, publisher1Data[i], (i + 1) * graphItemXGap, publisher1Data[i + 1]);
				ofPopStyle();
			}
		}

		for (int i = 0; i < publisher0Data.size() - 1; i++)
		{
			//ofPushStyle();
			//ofSetColor(255, 0, 0);
			//ofCircle(i * graphItemXGap, publisher0Data[i], 5);
			//ofSetColor(0, 255, 0);
			//ofCircle(i * graphItemXGap, publisher1Data[i], 5);
			//ofPopStyle();
		}

		for (int i = 0; i < publisher0Data.size() - 1; i++)
		{
			ofPushStyle();

			ofMesh bar;
			bar.addVertex(ofVec3f(i * graphItemXGap - (barWidth * 0.5), publisher0Data[i], 0));
			bar.addVertex(ofVec3f(i * graphItemXGap - (barWidth * 0.5) + barWidth, publisher0Data[i], 0));
			bar.addVertex(ofVec3f(i * graphItemXGap - (barWidth * 0.5), publisher1Data[i], 0));
			bar.addVertex(ofVec3f(i * graphItemXGap - (barWidth * 0.5) + barWidth, publisher1Data[i], 0));
			bar.addIndex(0);
			bar.addIndex(1);
			bar.addIndex(3);
			bar.addIndex(0);
			bar.addIndex(3);
			bar.addIndex(2);
			bar.addColor(ofColor(col0[0],col0[1],col0[2], col0[3]));
			bar.addColor(ofColor(col0[0],col0[1],col0[2], col0[3]));
			bar.addColor(ofColor(col1[0],col1[1],col1[2], col1[3]));
			bar.addColor(ofColor(col1[0],col1[1],col1[2], col1[3]));

			bar.drawFaces();

			//ofSetColor(255, 255, 0);
			//ofRect(i * graphItemXGap - (barWidth * 0.5), publisher0Data[i], barWidth, publisher1Data[i] - publisher0Data[i]);
			//ofSetColor(0, 0, 0);
			//ofLine(i * graphItemXGap, publisher0Data[i], i * graphItemXGap, publisher1Data[i]);
			ofPopStyle();
		}
	}
}



void BarGraph::addNewData(vector<int> newData)
{
	AbstractGraph::addNewData(newData);
}