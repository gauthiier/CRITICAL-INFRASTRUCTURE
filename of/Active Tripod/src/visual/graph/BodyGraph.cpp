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

		
		float xOffset = ofGetWidth() * AbstractGraph::minGraphPercent;
		float outputMin = (ofGetHeight() * 0.5) - graphHeightMax;
		float outputMax = (ofGetHeight() * 0.5) + graphHeightMax;

		if (isDrawBody)
		{
			// draw main part of graph (xOffset)
			ofMesh body;
			body.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
			for (int i = 0; i < publisher0Data.size() - 1; i++)
			{
				body.addVertex(ofVec3f(
					i * graphItemXGap + xOffset, 
					ofMap(publisher0Data[i].value, publisher0Data[i].min, publisher0Data[i].max, outputMin, outputMax), 
					0));
				body.addVertex(ofVec3f(
					i * graphItemXGap + xOffset, 
					ofMap(publisher1Data[i].value, publisher1Data[i].min, publisher1Data[i].max, outputMin, outputMax), 
					0));
			
				body.addColor(ofColor(col0[0],col0[1],col0[2], col0[3]));
				body.addColor(ofColor(col1[0],col1[1],col1[2], col1[3]));
			}
		
			body.drawFaces();
		}
		

		if (isDrawLines)
		{
			// draw lines
			ofPushStyle();
			ofPolyline poly0;
			ofPolyline poly1;
			for (int i = 0; i < publisher0Data.size() - 1; i++)
			{
				if (i < publisher0Data.size() - 1)
				{
					ofSetLineWidth(lineWidth);
					poly0.addVertex(ofPoint(
						i * graphItemXGap + xOffset,
						ofMap(publisher0Data[i].value, publisher0Data[i].min, publisher0Data[i].max, outputMin, outputMax)));
				
				
					poly1.addVertex(ofPoint(
						i * graphItemXGap + xOffset,
						ofMap(publisher1Data[i].value, publisher1Data[i].min, publisher1Data[i].max, outputMin, outputMax)));
				}
			}
		
			ofSetColor(col0[0],col0[1],col0[2], 255);
			poly0.draw();
			ofSetColor(col1[0],col1[1],col1[2], 255);
			poly1.draw();
			ofPopStyle();
		}
	}
}



void BodyGraph::addNewData(vector<DataObject> newData)
{
	AbstractGraph::addNewData(newData);
}