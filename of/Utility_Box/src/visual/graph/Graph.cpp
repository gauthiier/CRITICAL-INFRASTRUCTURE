//
//  Created by James Alliban on 11/01/2014.
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
float Graph::colFront[4];
float Graph::colBack[4];

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
	graphMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}




void Graph::update(ofVec3f activeCamPos)
{
	if (!isInfoTextSet)
	{
		isInfoTextSet = true;
		drawInfoToFbo();
	}

	if (hasColorChanged())
		updateColours();

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

	ofPushStyle();
		
	ofSetColor(255);
	ofSetLineWidth(2);
		
	graphMesh.drawFaces();
	//graphMesh.drawWireframe();

	//poly0.draw();
		
	ofPopStyle();
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



void Graph::setFboSettings()
{
	settings.width = fboW;
	settings.height = fboH;
	settings.internalformat = GL_RGBA;
	infoTextFbo.allocate(settings);
}


void Graph::drawInfoToFbo()
{

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

	float xOffset = 0;
	float outputMin = 0;
	float outputMax = graphHeightMax;
	
	if (newData.value == -999) newData.value = 0;
	if (newData.min == -999) newData.min = 0;
	if (newData.max == -999) newData.max = 0;

	if (newData.min != currentMin || newData.max != currentMax)
	{
		if (graphMesh.getVertices().size() > 0) clear();
	}

	currentValue = newData.value;
	currentMin = newData.min;
	currentMax = newData.max;
	
	int graphMeshSize = graphMesh.getVertices().size();
	vector<ofVec3f> *meshVertices = &graphMesh.getVertices();
	vector<ofFloatColor> *meshColours = &graphMesh.getColors();
	
	// add new vertex and colour
	float xTop = (graphMeshSize == 0) ? -(maxGraphWidth * 0.5) : (graphItemXGap * ((graphMeshSize * 0.5))) - (maxGraphWidth * 0.5);
	float yTop = ofMap(newData.value, newData.min, newData.max, outputMin, outputMax);
	if (isClampYValues) yTop = ofClamp(yTop, outputMin, outputMax);
	
	ofVec3f vertexTop = ofVec3f(xTop, yTop, centre.z);
	ofVec3f vertexBottom = ofVec3f(xTop, 0, centre.z);
	
	graphMesh.addVertex(vertexTop);
	graphMesh.addVertex(vertexBottom);
	

	ofColor col;
	col.r = (int)ofMap(graphID, 0, 29, colFront[0], colBack[0]);
	col.g = (int)ofMap(graphID, 0, 29, colFront[1], colBack[1]);
	col.b = (int)ofMap(graphID, 0, 29, colFront[2], colBack[2]);
	col.a = (int)ofMap(graphID, 0, 29, colFront[3], colBack[3]);
	
	
	//= ofColor(ofMap(
	//	graphID, 0, 29, 0, 255), 
	//	ofMap(graphID, 0, 29, 255, 0), 
	//	ofMap(graphID, 0, 29, 150, 50), 
	//	255);
	
	//if (ofRandomuf() < 0.1) col = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
	
	graphMesh.addColor(col);
	graphMesh.addColor(ofColor(col.r, col.g, col.b, 0));
	
	if (graphMeshSize * 0.5 >= maxData)
	{
		// loop through all vertices (apart from the last) and nudge them all to the left.
		for (int i = 0; i < graphMeshSize; i += 2)
		{
			meshVertices->at(i).x -= graphItemXGap;
			meshVertices->at(i + 1).x -= graphItemXGap;
		}
		graphMesh.removeVertex(0);
		graphMesh.removeVertex(0);
		graphMesh.removeColor(0);
		graphMesh.removeColor(0);
	}
}


void Graph::clear()
{
	graphMesh.clear();
	setFboSettings();
	//drawInfoToFbo();
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




bool Graph::hasColorChanged()
{
	if (colFront[0] != colBack[0] || colFront[1] != colBack[1] || colFront[2] != colBack[2] || colFront[3] != colBack[3])
		return true;
	else
		return false;
}



void Graph::updateColours()
{
	ofColor col;
	col.r = (int)ofMap(graphID, 0, 29, colFront[0], colBack[0]);
	col.g = (int)ofMap(graphID, 0, 29, colFront[1], colBack[1]);
	col.b = (int)ofMap(graphID, 0, 29, colFront[2], colBack[2]);
	col.a = (int)ofMap(graphID, 0, 29, colFront[3], colBack[3]);


	for (int i = 0; i < graphMesh.getColors().size(); i+=2)
	{
		graphMesh.setColor(i, col);
		graphMesh.setColor(i+1, ofColor(col.r, col.g, col.b, 0));
	}
}