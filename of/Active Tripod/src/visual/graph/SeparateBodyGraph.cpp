//
//  Created by James Alliban on 11/01/2014.
//
//

#include "SeparateBodyGraph.h"
#include "testApp.h"


void SeparateBodyGraph::setup()
{
	AbstractGraph::setup();
	app = (testApp*)ofGetAppPtr();
	graphName = "SEPARATE_BODY";
}


void SeparateBodyGraph::update()
{
	AbstractGraph::update();
}																		


void SeparateBodyGraph::draw()
{
	if (app->gui.getVisible())
	{
		float timePerScreenfull = (float)maxData * sendDataSpeed;
		ofDrawBitmapString("Time to fill screen:" + ofToString(timePerScreenfull), 500, 150);
	}

	if (publisher0Data.size() > 1)
	{
		ofMesh body0 = getMesh(publisher0Data, col0, 0);
		ofMesh body1 = getMesh(publisher1Data, col1, 1);

		if (body0.getVertices().size() > 2)
		{
			currentPub0Point = ofPoint(body0.getVertex(body0.getVertices().size() - 2).x, body0.getVertex(body0.getVertices().size() - 2).y);
			currentPub1Point = ofPoint(body0.getVertex(body1.getVertices().size() - 2).x, body1.getVertex(body1.getVertices().size() - 2).y);
		}

		float xOffset = ofGetWidth() * AbstractGraph::minGraphPercent;
		float outputMin = (ofGetHeight() * 0.5) - ((ofGetHeight() * 0.5) * graphHeightMax);
		float outputMax = (ofGetHeight() * 0.5) + ((ofGetHeight() * 0.5) * graphHeightMax);
		

		// draw lines
		ofPushStyle();
		ofPolyline poly0;
		ofPolyline poly1;
		for (int i = 0; i < publisher0Data.size() - 1; i++)
		{
			if (i < publisher0Data.size() - 1)
			{
				ofSetLineWidth(lineWidth);
				poly0.addVertex(body0.getVertex(i*2));
				poly1.addVertex(body1.getVertex(i*2));
			}
		}

		ofVec2f centroid0 = poly0.getCentroid2D();
		ofVec2f centroid1 = poly1.getCentroid2D();

		float av0;
		float av1;

		for (int i = 0; i < poly0.size(); i++)
		{
			av0 += poly0[i].y;
			av1 += poly1[i].y;
		}
		av0 /= poly0.size();
		av1 /= poly1.size();
		
		int lineAlpha = 255;
		if (!isDrawLines) lineAlpha = 0;
		
		graphTextPnt0 = currentPub0Point;
		graphTextPnt1 = currentPub1Point;

		ofPushMatrix();
		if (publisher0Data.size() >= maxData) 
		{
			float meshXOffset = ofMap(normalisedTimeInc, 0, 1, 0, -graphItemXGap);
			ofTranslate(meshXOffset, 0);
			graphTextPnt0.x += meshXOffset;
			graphTextPnt1.x += meshXOffset;
		}
		
		if (av0 < av1)
		{
			body0.drawFaces();
			ofSetColor(col0[0],col0[1],col0[2], lineAlpha);
			poly0.draw();
			
			body1.drawFaces();
			ofSetColor(col1[0],col1[1],col1[2], lineAlpha);
			poly1.draw();
		}
		else
		{
			body1.drawFaces();
			ofSetColor(col1[0],col1[1],col1[2], lineAlpha);
			poly1.draw();

			body0.drawFaces();
			ofSetColor(col0[0],col0[1],col0[2], lineAlpha);
			poly0.draw();
		}
		ofPopMatrix();
		
		ofPopStyle();
	}
}


ofMesh SeparateBodyGraph::getMesh(vector<DataObject> publisherData, float* col, int graphID)
{
	ofMesh bodyMesh;
	float xOffset = ofGetWidth() * AbstractGraph::minGraphPercent;
	float outputMin = (ofGetHeight() * 0.5) - ((ofGetHeight() * 0.5) * graphHeightMax);
	float outputMax = (ofGetHeight() * 0.5) + ((ofGetHeight() * 0.5) * graphHeightMax);

	// draw main part of graph (xOffset)
	bodyMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	for (int i = 0; i < publisherData.size() - 1; i++)
	{
		if (i < publisherData.size() - 2)
		{
			bodyMesh.addVertex(ofVec3f(
				i * graphItemXGap + xOffset, 
				ofMap(publisherData[i].value, publisherData[i].min, publisherData[i].max, outputMin, outputMax), 
				0));
			bodyMesh.addVertex(ofVec3f(
				i * graphItemXGap + xOffset, 
				ofGetHeight() * graphEndPercent, 
				0));
		}
		else
		{
			float targetY0 = ofMap(publisherData[i].value, publisherData[i].min, publisherData[i].max, outputMin, outputMax);
			float prevY0 = ofMap(publisherData[i-1].value, publisherData[i-1].min, publisherData[i-1].max, outputMin, outputMax);
			endPoint0.y = ofMap(normalisedTimeInc, 0, 1, prevY0, targetY0);
			endPoint0.x = (i-1) * graphItemXGap + xOffset + (graphItemXGap * normalisedTimeInc);
			
			if (graphID == 0)
			{
				animatedVal0 = ofMap(endPoint0.y, outputMin, outputMax, publisher0Data.back().min, publisher0Data.back().max);
				animatedVal0LLI = ofMap(endPoint0.y, outputMin, outputMax, publisher0Data.back().min, publisher0Data.back().max);
				//animatedVal0 = 99111222333;
				//animatedVal0LLI = 99111222333;
			}
			else
			{
				animatedVal1 = ofMap(endPoint0.y, outputMin, outputMax, publisher1Data.back().min, publisher1Data.back().max);
				animatedVal1LLI = ofMap(endPoint0.y, outputMin, outputMax, publisher1Data.back().min, publisher1Data.back().max);
			}

			bodyMesh.addVertex(ofVec3f(
				endPoint0.x, 
				endPoint0.y, 
				0));
			bodyMesh.addVertex(ofVec3f(
				endPoint0.x, 
				ofGetHeight() * graphEndPercent, 
				0));
		}

			
		bodyMesh.addColor(ofColor(col[0],col[1],col[2], col[3]));
		bodyMesh.addColor(ofColor(col[0],col[1],col[2], 0));
	}
	return bodyMesh;
}



void SeparateBodyGraph::addNewData(vector<DataObject> newData)
{
	AbstractGraph::addNewData(newData);
}