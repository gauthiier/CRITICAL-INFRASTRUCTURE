//
//  Created by James Alliban on 08/01/2014.
//
//

#include "BodyGraph.h"
#include "testApp.h"


void BodyGraph::setup()
{
	AbstractGraph::setup();
	app = (testApp*)ofGetAppPtr();
	graphName = "BODY";
}


void BodyGraph::update()
{
	AbstractGraph::update();
}																			


void BodyGraph::draw()
{
	if (app->gui.getVisible())
	{
		float timePerScreenfull = (float)maxData * sendDataSpeed;
		//printf("timePerScreenfull:%f, maxData:%i, sendDataSpeed:%f \n", timePerScreenfull, maxData, sendDataSpeed);
		ofDrawBitmapString("Time to fill screen:" + ofToString(timePerScreenfull), 500, 150);
	}


	if (publisher0Data.size() > 1)
	{
		float xOffset = ofGetWidth() * AbstractGraph::minGraphPercent;
		float outputMin = (ofGetHeight() * 0.5) - ((ofGetHeight() * 0.5) * graphHeightMax);
		float outputMax = (ofGetHeight() * 0.5) + ((ofGetHeight() * 0.5) * graphHeightMax);

		if (isDrawBody)
		{
			// draw main part of graph (xOffset)
			ofMesh body;
			body.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
			
			for (int i = 0; i < publisher0Data.size() - 1; i++)
			{
				if (i < publisher0Data.size() - 2)
				{
					body.addVertex(ofVec3f(
						i * graphItemXGap + xOffset, 
						ofMap(publisher0Data[i].value, publisher0Data[i].max, publisher0Data[i].min, outputMin, outputMax), 
						0));
					body.addVertex(ofVec3f(
						i * graphItemXGap + xOffset, 
						ofMap(publisher1Data[i].value, publisher1Data[i].max, publisher1Data[i].min, outputMin, outputMax), 
						0));
				}
				else
				{
					float targetY0 = ofMap(publisher0Data[i].value, publisher0Data[i].max, publisher0Data[i].min, outputMin, outputMax);
					float prevY0 = ofMap(publisher0Data[i-1].value, publisher0Data[i-1].max, publisher0Data[i-1].min, outputMin, outputMax);
					endPoint0.y = ofMap(normalisedTimeInc, 0, 1, prevY0, targetY0);
					
					float targetY1 = ofMap(publisher1Data[i].value, publisher1Data[i].max, publisher1Data[i].min, outputMin, outputMax);
					float prevY1 = ofMap(publisher1Data[i-1].value, publisher1Data[i-1].max, publisher1Data[i-1].min, outputMin, outputMax);
					endPoint1.y = ofMap(normalisedTimeInc, 0, 1, prevY1, targetY1);
					
					endPoint0.x = (i-1) * graphItemXGap + xOffset + (graphItemXGap * normalisedTimeInc);
					endPoint1.x = endPoint0.x;

					body.addVertex(ofVec3f(
						endPoint0.x, 
						endPoint0.y, 
						0));
					body.addVertex(ofVec3f(
						endPoint1.x, 
						endPoint1.y, 
						0));

					//float mahousive = 1000000000;
					//animatedVal0 = ofMap(endPoint0.y * mahousive, outputMin * mahousive, outputMax * mahousive, publisher0Data.back().min * mahousive, publisher0Data.back().max * mahousive);
					//animatedVal0LLI = ofMap(endPoint0.y * mahousive, outputMin * mahousive, outputMax * mahousive, publisher0Data.back().min * mahousive, publisher0Data.back().max * mahousive);
					animatedVal0 = ofMap(endPoint0.y, outputMax, outputMin, publisher0Data.back().min, publisher0Data.back().max);
					animatedVal0LLI = ofMap(endPoint0.y, outputMax, outputMin, publisher0Data.back().min, publisher0Data.back().max);
					
					animatedVal1 = ofMap(endPoint1.y, outputMax, outputMin, publisher1Data.back().min, publisher1Data.back().max);
					animatedVal1LLI = ofMap(endPoint1.y, outputMax, outputMin, publisher1Data.back().min, publisher1Data.back().max);
					
				}
				body.addColor(ofColor(col0[0],col0[1],col0[2], col0[3]));
				body.addColor(ofColor(col1[0],col1[1],col1[2], col1[3]));

				if (i == publisher0Data.size() - 2)
				{
					currentPub0Point = body.getVertex(body.getVertices().size() - 2);
					currentPub1Point = body.getVertices().back();
				}
			}
		
			ofPushMatrix();
			if (publisher0Data.size() >= maxData) ofTranslate(ofMap(normalisedTimeInc, 0, 1, 0, -graphItemXGap), 0);
			body.drawFaces();
			ofPopMatrix();
		}
					
		graphTextPnt0 = currentPub0Point;
		graphTextPnt1 = currentPub1Point;
		
		if (publisher0Data.size() >= maxData) 
		{
			float meshXOffset = ofMap(normalisedTimeInc, 0, 1, 0, -graphItemXGap);
			graphTextPnt0.x += meshXOffset;
			graphTextPnt1.x += meshXOffset;
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
					if (i < publisher0Data.size() - 2)
					{
						poly0.addVertex(ofPoint(
							i * graphItemXGap + xOffset,
							ofMap(publisher0Data[i].value, publisher0Data[i].max, publisher0Data[i].min, outputMin, outputMax)));
				
				
						poly1.addVertex(ofPoint(
							i * graphItemXGap + xOffset,
							ofMap(publisher1Data[i].value, publisher1Data[i].max, publisher1Data[i].min, outputMin, outputMax)));
					}
					else
					{
						poly0.addVertex(ofPoint(
							endPoint0.x,
							endPoint0.y));
				
				
						poly1.addVertex(ofPoint(
							endPoint1.x,
							endPoint1.y));
					}
				}
			}

		
			ofSetLineWidth(lineWidth);
			ofPushMatrix();
			if (publisher0Data.size() >= maxData) ofTranslate(ofMap(normalisedTimeInc, 0, 1, 0, -graphItemXGap), 0);
			ofSetColor(col0[0],col0[1],col0[2], 255);
			poly0.draw();
			ofSetColor(col1[0],col1[1],col1[2], 255);
			poly1.draw();
			ofPopMatrix();
			ofPopStyle();
		}
	}
}



void BodyGraph::addNewData(vector<DataObject> newData)
{
	AbstractGraph::addNewData(newData);
}