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
		ofMesh body0 = getMesh(publisher0Data, col0);
		ofMesh body1 = getMesh(publisher1Data, col1);
		
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
				poly0.addVertex(ofPoint(
					i * graphItemXGap + xOffset,
					ofMap(publisher0Data[i].value, publisher0Data[i].min, publisher0Data[i].max, outputMin, outputMax)));
				
				
				poly1.addVertex(ofPoint(
					i * graphItemXGap + xOffset,
					ofMap(publisher1Data[i].value, publisher1Data[i].min, publisher1Data[i].max, outputMin, outputMax)));
			}
		}
		

		
		ofVec2f centroid0 = poly0.getCentroid2D();
		ofVec2f centroid1 = poly1.getCentroid2D();

		printf("centroid0.y:%f, centroid1.y:%f\n", centroid0.y, centroid1.y);
		
		float av0;
		float av1;

		for (int i = 0; i < poly0.size(); i++)
		{
			av0 += poly0[i].y;
			av1 += poly1[i].y;
		}
		av0 /= poly0.size();
		av1 /= poly1.size();
		
		printf("av0:%f, av1:%f\n", av0, av1);

		int lineAlpha = 255;
		if (!isDrawLines) lineAlpha = 0;

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

		if (isDrawLines)
		{
			if (av0 > av1)
			{
				
				
			}
			else
			{
				
				
			}
		}
		
		ofPopStyle();
	}
}


ofMesh SeparateBodyGraph::getMesh(vector<DataObject> publisherData, float* col)
{
	ofMesh bodyMesh;
	float xOffset = ofGetWidth() * AbstractGraph::minGraphPercent;
	float outputMin = (ofGetHeight() * 0.5) - ((ofGetHeight() * 0.5) * graphHeightMax);
	float outputMax = (ofGetHeight() * 0.5) + ((ofGetHeight() * 0.5) * graphHeightMax);

	// draw main part of graph (xOffset)
	bodyMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	for (int i = 0; i < publisherData.size() - 1; i++)
	{
		bodyMesh.addVertex(ofVec3f(
			i * graphItemXGap + xOffset, 
			ofMap(publisherData[i].value, publisherData[i].min, publisherData[i].max, outputMin, outputMax), 
			0));
		bodyMesh.addVertex(ofVec3f(
			i * graphItemXGap + xOffset, 
			ofGetHeight() * graphEndPercent, 
			0));
			
		bodyMesh.addColor(ofColor(col[0],col[1],col[2], col[3]));
		bodyMesh.addColor(ofColor(col[0],col[1],col[2], 0));
	}
	return bodyMesh;
}



void SeparateBodyGraph::addNewData(vector<DataObject> newData)
{
	AbstractGraph::addNewData(newData);
}