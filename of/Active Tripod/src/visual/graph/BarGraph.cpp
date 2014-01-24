#include "BarGraph.h"
#include "testApp.h"

void BarGraph::setup()
{
	AbstractGraph::setup();
	app = (testApp*)ofGetAppPtr();
	graphItemXGap = 10;
	graphName = "BAR";
}


void BarGraph::update()
{
	AbstractGraph::update();
}


void BarGraph::draw()
{
	if (app->gui.getVisible())
	{
		int timePerScreenfull = maxData * sendDataSpeed;
		ofDrawBitmapString("Time to fill screen:" + ofToString(timePerScreenfull), 500, 150);
	}


	if (publisher0Data.size() > 1)
	{
		float xOffset = ofGetWidth() * AbstractGraph::minGraphPercent;
		float outputMin = (ofGetHeight() * 0.5) - ((ofGetHeight() * 0.5) * graphHeightMax);
		float outputMax = (ofGetHeight() * 0.5) + ((ofGetHeight() * 0.5) * graphHeightMax);


		
		ofPushMatrix();
		//if (publisher0Data.size() >= maxData) 
		//ofTranslate(ofMap(normalisedTimeInc, 0, 1, 0, -graphItemXGap*0.5), 0);

		for (int i = 0; i < publisher0Data.size() - 1; i++)
		{
			ofPushStyle();

			ofMesh bar;
			float rectTLX = i * graphItemXGap - (barWidth * 0.5) + xOffset;
			float rectTLY = ofMap(publisher0Data[i].value, publisher0Data[i].min, publisher0Data[i].max, outputMin, outputMax);
			
			float rectTRX = i * graphItemXGap - (barWidth * 0.5) + barWidth + xOffset;
			float rectTRY = ofMap(publisher0Data[i].value, publisher0Data[i].min, publisher0Data[i].max, outputMin, outputMax);
			
			float rectBLX = i * graphItemXGap - (barWidth * 0.5) + xOffset;
			float rectBLY = ofMap(publisher1Data[i].value, publisher1Data[i].min, publisher1Data[i].max, outputMin, outputMax);
			
			float rectBRX = i * graphItemXGap - (barWidth * 0.5) + barWidth + xOffset;
			float rectBRY = ofMap(publisher1Data[i].value, publisher1Data[i].min, publisher1Data[i].max, outputMin, outputMax);

			if (i == publisher0Data.size() - 2)
			{
				currentPub0Point = ofPoint(rectTRX, rectTRY);
				currentPub1Point = ofPoint(rectBRX, rectBRY);
			}

			bar.addVertex(ofVec3f(rectTLX, rectTLY, 0));
			bar.addVertex(ofVec3f(rectTRX, rectTRY, 0));
			bar.addVertex(ofVec3f(rectBLX, rectBLY, 0));
			bar.addVertex(ofVec3f(rectBRX, rectBRY, 0));
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

			ofPopStyle();
		}

		ofPopMatrix();
	}
}



void BarGraph::addNewData(vector<DataObject> newData)
{
	AbstractGraph::addNewData(newData);
}