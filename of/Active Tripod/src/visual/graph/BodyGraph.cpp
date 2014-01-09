//
//  Created by James Alliban on 08/01/2014.
//
//

#include "BodyGraph.h"


void BodyGraph::setup()
{
	AbstractGraph::setup();
}


void BodyGraph::update()
{
//	if (ofGetFrameNum() % 30 == 0)
//		printf("publisher0Data.size():%i \n", publisher0Data.size());
}


void BodyGraph::draw()
{
	if (publisher0Data.size() > 1)
	{
		//for (int i = 0; i < publisher0Data.size() - 1; i++)
		//{
		//	ofPushStyle();
		//	ofSetColor(255, 0, 0);
		//	ofCircle(i * graphItemXGap, publisher0Data[i], 5);
		//	ofSetColor(0, 255, 0);
		//	ofCircle(i * graphItemXGap, publisher1Data[i], 5);
		//	ofPopStyle();
		//}


		ofMesh body;
		body.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		for (int i = 0; i < publisher0Data.size() - 1; i++)
		{
			//body.addVertex(ofVec3f(i * graphItemXGap, publisher0Data[i], 0));
			//body.addVertex(ofVec3f(i * graphItemXGap, publisher1Data[i], 0));
			
			body.addColor(ofColor(col0[0],col0[1],col0[2], col0[3]));
			body.addColor(ofColor(col1[0],col1[1],col1[2], col1[3]));
		}
		
		body.drawFaces();

		
		for (int i = 0; i < publisher0Data.size() - 1; i++)
		{
			if (i < publisher0Data.size() - 2)
			{
				//ofPushStyle();
				//ofSetLineWidth(lineWidth);
				//ofSetColor(col0[0],col0[1],col0[2], 255);
				//ofLine(i * graphItemXGap, publisher0Data[i], (i + 1) * graphItemXGap, publisher0Data[i + 1]);
				//ofSetColor(col1[0],col1[1],col1[2], 255);
				//ofLine(i * graphItemXGap, publisher1Data[i], (i + 1) * graphItemXGap, publisher1Data[i + 1]);
				//ofPopStyle();
			}
		}

	}
}



void BodyGraph::addNewData(vector<DataObject> newData)
{
	AbstractGraph::addNewData(newData);
}