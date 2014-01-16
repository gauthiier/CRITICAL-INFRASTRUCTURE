//
//  Created by James Alliban on 11/01/2014.
//
//

#include "Graph.h"
#include "testApp.h"

float Graph::maxGraphWidth;
bool Graph::isDrawBody;
bool Graph::isDrawLines;
bool Graph::isClampYValues;
float Graph::graphItemXGap;
float Graph::lineThickness;
float Graph::graphHeightMax;
float Graph::graphEndPercent;
float Graph::zRange;
float Graph::graphTextZOffset;

float Graph::lineLength;
float Graph::lineSpacing;
float Graph::textSize;
float Graph::fboW;
float Graph::fboH;
float Graph::textY;
ofPoint Graph::textPnt;

Graph::Graph(int _graphID)
{
	app = (testApp*)ofGetAppPtr();
	graphID = _graphID;

	isInfoTextSet = false;
}




void Graph::update(ofVec3f activeCamPos)
{
	if (publisher0Data.size() > 0 && publisher0Data.back().info != "" && !isInfoTextSet)
	{
		isInfoTextSet = true;
		drawInfoToFbo();
	}


	ofVec3f camPos = activeCamPos;
	centre = ofVec3f(0.1, 0.1, ofMap(graphID, 0, 29, -zRange, zRange));
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
	drawGraphBody();
	drawGraphText();
}


void Graph::drawGraphBody()
{	
	if (!isDrawBody) return;

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
				ofSetLineWidth(lineThickness);
				ofVec3f vec = ofVec3f(i * graphItemXGap - (maxGraphWidth * 0.5),
					ofMap(publisher0Data[i].value, publisher0Data[i].min, publisher0Data[i].max, outputMin, outputMax),
					centre.z);

				if (isClampYValues) vec.y = ofClamp(vec.y, outputMin, outputMax);
				
				poly0.addVertex(vec);
			}
		}
		
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


void Graph::drawGraphText()
{
	ofPushStyle();
	ofSetColor(255, 255);
	ofPushMatrix();
	ofTranslate(textPnt.x, textPnt.y, centre.z + graphTextZOffset);
	ofRotateX(-90);
	ofScale(0.1, 0.1);
	infoTextFbo.draw(0, 0);
	ofPopMatrix();
	ofPopStyle();
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
		ofVec3f vecH = ofVec3f(
			i * graphItemXGap - (maxGraphWidth * 0.5), 
			ofMap(publisherData[i].value, publisherData[i].min, publisherData[i].max, outputMin, outputMax), 
			centre.z);
		
		if (isClampYValues) vecH.y = ofClamp(vecH.y, outputMin, outputMax);
		bodyMesh.addVertex(vecH);

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


void Graph::setFboSettings()
{
	settings.width = fboW;
	settings.height = fboH;
	settings.internalformat = GL_RGBA;
	infoTextFbo.allocate(settings);
}


void Graph::drawInfoToFbo()
{
	string infoText = "";

	if (publisher0Data.size() > 0) 
	{
		infoText = info;
	}

	//printf("---- infoText = %s \n", infoText.c_str());

	text->setLineLength(lineLength);
    text->setLineSpacing(lineSpacing);
	text->setSize(textSize);
	text->setAlignment(FTGL_ALIGN_LEFT);

	ofPushStyle();
	
	infoTextFbo.begin();
	ofClear(0, 0, 0, 0);
	ofSetColor(0, 0);
	ofRect(0, 0, settings.width, settings.height);
	ofSetColor(255, 255);
	//ofScale(0.5, 0.5);

	text->drawString(ofToString(graphID), 0, textY);
	infoTextFbo.end();
	
	ofPopStyle();
}


void Graph::addNewData(DataObject newData)
{
	info = explode("\n", newData.info)[0];
	publisher0Data.push_back(newData);
	while (publisher0Data.size() > maxData)
		publisher0Data.erase(publisher0Data.begin());
}


void Graph::clear()
{
	publisher0Data.clear();
	setFboSettings();
	drawInfoToFbo();
}

vector<string> Graph::explode(const string &delimiter, const string &str)
{
    vector<string> arr;

    int strleng = str.length();
    int delleng = delimiter.length();
    if (delleng==0)
        return arr;//no change

    int i=0;
    int k=0;
    while( i<strleng )
    {
        int j=0;
        while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
        if (j==delleng)//found delimiter
        {
            arr.push_back(  str.substr(k, i-k) );
            i+=delleng;
            k=i;
        }
        else
        {
            i++;
        }
    }
    arr.push_back(  str.substr(k, i-k) );
    return arr;
}