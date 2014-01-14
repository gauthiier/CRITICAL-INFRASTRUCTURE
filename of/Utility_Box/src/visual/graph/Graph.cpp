//
//  Created by James Alliban on 11/01/2014.
//
//

#include "Graph.h"
#include "testApp.h"

float Graph::minGraphPercent;
float Graph::maxGraphPercent;
float Graph::maxGraphWidth;
bool Graph::isDrawLines;
float Graph::graphItemXGap;
float Graph::lineWidth;
float Graph::graphHeightMax;
float Graph::graphEndPercent;

Graph::Graph(int _graphID)
{
	app = (testApp*)ofGetAppPtr();
	graphID = _graphID;
}



void Graph::update(ofVec3f activeCamPos)
{
	ofVec3f camPos = activeCamPos;
	centre = ofVec3f(0.1, 0.1, ofMap(graphID, 0, 29, -50, 50));
	distToCam = sqrt(double(ABS(camPos.x - centre.x) * ABS(camPos.x - centre.x) * ABS(camPos.x - centre.x) + 
		ABS(camPos.y - centre.y) * ABS(camPos.y - centre.y) * ABS(camPos.y - centre.y) + 
		ABS(camPos.z - centre.z) * ABS(camPos.z - centre.z) * ABS(camPos.z - centre.z)));
	maxData = maxGraphWidth /  graphItemXGap;
}



void Graph::draw()
{
	if (app->gui.isVisible)
	{
		float timePerScreenfull = (float)maxData * app->dataManager.sendDataSpeed;
		ofDrawBitmapString("Time to fill screen:" + ofToString(timePerScreenfull), 500, 150);
	}
	
	if (publisher0Data.size() > 1)
	{
		ofMesh body0 = getMesh(publisher0Data, col0);

		if (body0.getVertices().size() > 2)
		{
			currentPub0Point = ofPoint(body0.getVertex(body0.getVertices().size() - 2).x, body0.getVertex(body0.getVertices().size() - 2).y);
		}

		float xOffset = 0;
		float outputMin = 0;
		float outputMax = graphHeightMax;

		// draw lines
		ofPushStyle();
		ofPolyline poly0;
		for (int i = 0; i < publisher0Data.size() - 1; i++)
		{
			if (i < publisher0Data.size() - 1)
			{
				ofSetLineWidth(lineWidth);
				poly0.addVertex(ofVec3f(
					i * graphItemXGap - (maxGraphWidth * 0.5),
					ofMap(publisher0Data[i].value, publisher0Data[i].min, publisher0Data[i].max, outputMin, outputMax),
					centre.z));
			}
		}

		//ofVec3f(
		//	i * graphItemXGap - (maxGraphWidth * 0.5), 
		//	ofMap(publisherData[i].value, publisherData[i].min, publisherData[i].max, outputMin, outputMax), 
		//	0)
		
		ofVec2f centroid0 = poly0.getCentroid2D();

		float av0;
		for (int i = 0; i < poly0.size(); i++)
			av0 += poly0[i].y;

		av0 /= poly0.size();
		
		int lineAlpha = 255;
		if (!isDrawLines) lineAlpha = 0;
		
		body0.drawFaces();
		//body0.drawWireframe();
		//ofSetColor(col0[0],col0[1],col0[2], lineAlpha);
		
		//poly0.draw();
		
		ofPopStyle();
	}
}


ofMesh Graph::getMesh(vector<DataObject> publisherData, float* col)
{
	ofMesh bodyMesh;
	float xOffset = 0;
	float outputMin = 0;
	float outputMax = graphHeightMax;

	// draw main part of graph (xOffset)
	bodyMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	for (int i = 0; i < publisherData.size() - 1; i++)
	{
		bodyMesh.addVertex(ofVec3f(
			i * graphItemXGap - (maxGraphWidth * 0.5), 
			ofMap(publisherData[i].value, publisherData[i].min, publisherData[i].max, outputMin, outputMax), 
			centre.z));
		bodyMesh.addVertex(ofVec3f(
			i * graphItemXGap - (maxGraphWidth * 0.5), 
			0, 
			centre.z));
			
		ofColor tempCol = ofColor(ofMap(graphID, 0, 29, 0, 255), ofMap(graphID, 0, 29, 255, 0), ofMap(graphID, 0, 29, 150, 50), 255);
		bodyMesh.addColor(tempCol);
		bodyMesh.addColor(ofColor(tempCol.r, tempCol.g, tempCol.b, 0));
		//bodyMesh.addColor(ofColor(col[0],col[1],col[2], 255));
		//bodyMesh.addColor(ofColor(col[0],col[1],col[2], 0));
	}

	
	return bodyMesh;
}



void Graph::addNewData(DataObject newData)
{
	publisher0Data.push_back(newData);
	while (publisher0Data.size() > maxData && publisher0Data.size() > maxData)
		publisher0Data.erase(publisher0Data.begin());
}


void Graph::clear()
{
	publisher0Data.clear();
}