//
//  gui->cpp
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#include "Scene.h"


void Scene::setup()
{
	vidGrabber.initGrabber(1280, 720);
	vidGrabber.setDesiredFrameRate(30);

	bgImg.loadImage("images/tanks.jpg");
	rgbShader.load("shaders/RGBShader");
	barGraph.setup();
	bodyGraph.setup();

    text.loadFont("fonts/Roboto-Light.ttf", 8);
}


void Scene::update()
{
	vidGrabber.update();
	
	activeGraph->update();

	text.setLineLength(lineLength);
    text.setLineSpacing(lineSpacing);
	text.setSize(textSize);
}


void Scene::draw()
{
	drawVideo();
	activeGraph->draw();
	drawHUDBG();
	drawHUDCopy();
	drawHUDColourBars();
}

void Scene::drawVideo()
{
	rgbShader.begin();

	rgbShader.setUniform1f("brightness", brightness);
	rgbShader.setUniform1f("contrast", contrast);
	rgbShader.setUniform1f("saturation", saturation);
	rgbShader.setUniform1f("red", red);
	rgbShader.setUniform1f("green", green);
	rgbShader.setUniform1f("blue", blue);
	rgbShader.setUniform1f("alpha", alpha);
	
	float vidW = ofGetWidth() * videoWidthPercentage;
	float vidH = ofGetHeight() * videoHeightPercentage;

	ofPushMatrix();
	ofTranslate((ofGetWidth() - vidW) * 0.5, (ofGetHeight() - vidH) * 0.5);
	if (isVideoVisible)
		vidGrabber.draw(0, 0, vidW, vidH);
	if (isImageVisible)
	    bgImg.draw(0, 0, vidW, vidH);
	ofPopMatrix();

	rgbShader.end();
}

void Scene::drawHUDBG()
{
	ofPushStyle();
	ofSetColor(hudColour[0], hudColour[1], hudColour[2], hudColour[3]);
	ofBeginShape();
	
	ofVertex(0, 0);
	ofVertex(ofGetWidth(), 0);
	ofVertex(ofGetWidth(), ofGetHeight());
	ofVertex(0, ofGetHeight());
		
	ofNextContour(true);

	float radiusW = (ofGetWidth() * 0.5) * hudHoleWidthPercentage;
	float radiusH = (ofGetHeight() * 0.5) * hudHoleHeightPercentage;
	
	for (int i = 0; i < (int)circlePointSize; i++)
	{
		float x = (ofGetWidth() * 0.5) + cos(((float)i / (int)circlePointSize) * TWO_PI) * radiusW;
		float y = (ofGetHeight() * 0.5) + sin(((float)i / (int)circlePointSize) * TWO_PI) * radiusH;
		ofVertex(x, y);
	}

	ofEndShape(true);
	ofPopStyle();

	ofFill();
}


void Scene::drawHUDCopy()
{
	drawTextBox(tlStr, "TOP LEFT");
	drawTextBox(trStr, "TOP RIGHT");
	
	vector<DataObject> *p0Data = &activeGraph->publisher0Data;
	vector<DataObject> *p1Data = &activeGraph->publisher1Data;

	int amountToAverage = MIN(p0Data->size(), averageAmount);
	if (p0Data->size() > 2)
	{
		float average0 = 0;
		for (int i = 0; i < (int)amountToAverage; i++)
			average0 += p0Data->at(p0Data->size() - i - 1).value;
		average0 /= (int)amountToAverage;

		//	(p0Data->back() + p0Data->at(p0Data->size() - 2) + p0Data->at(p0Data->size() - 2))
		blStr = "Increase: " + ofToString(p0Data->back().value - p0Data->at(p0Data->size() - 2).value) + "\n" +
			"Current Value: " + ofToString(p0Data->back().value) + "\n" + 
			"Running average: " + ofToString(average0);
		drawTextBox(blStr, "BOTTOM LEFT");
		

		float average1 = 0;
		for (int i = 0; i < (int)amountToAverage; i++)
			average1 += p1Data->at(p1Data->size() - i - 1).value;
		average1 /= (int)amountToAverage;

		brStr = "Increase: " + ofToString(p1Data->back().value - p1Data->at(p1Data->size() - 2).value) + "\n" +
			"Current Value: " + ofToString(p1Data->back().value) + "\n" + 
			"Running average: " + ofToString(average1);
		drawTextBox(brStr, "BOTTOM RIGHT");
	}
}


void Scene::drawTextBox(string copy, string align)
{
	ofPushStyle();
	ofSetColor(textColour[0], textColour[1], textColour[2], textColour[3]);
	ofPushMatrix();
	if (align == "TOP LEFT")
	{
		text.setAlignment(FTGL_ALIGN_LEFT);
		ofTranslate(xMargin, yMargin);
	}
	else if (align == "TOP RIGHT")
	{
		text.setAlignment(FTGL_ALIGN_RIGHT);
		ofTranslate(ofGetWidth() - xMargin - lineLength, yMargin);
	}
	else if (align == "BOTTOM LEFT")
	{
		ofTranslate(xMargin, ofGetHeight() - yMargin - yMarginBottomOffset);
		text.setAlignment(FTGL_ALIGN_LEFT);
	}
	if (align == "BOTTOM RIGHT")
	{
		text.setAlignment(FTGL_ALIGN_RIGHT);
		ofTranslate(ofGetWidth() - xMargin - lineLength, ofGetHeight() - yMargin - yMarginBottomOffset);
	}

	text.drawString(copy, 0, 0);
	
	//printf("%s text.getXHeight() = %f\n", align.c_str(), text.getStringBoundingBox(copy, xMargin, yMargin));

	ofPopMatrix();
	ofPopStyle();
}



void Scene::drawHUDColourBars()
{
	ofPushStyle();
	
	ofSetColor(activeGraph->col0[0], activeGraph->col0[1], activeGraph->col0[2], activeGraph->col0[3]);
	ofRect(xMargin, yMargin + topColourBoxXOffset, lineLength, colourBoxThickness);

	ofSetColor(activeGraph->col0[0], activeGraph->col0[1], activeGraph->col0[2], activeGraph->col0[3]);
	ofRect(xMargin, ofGetHeight() - yMargin - yMarginBottomOffset + bottomColourBoxXOffset, lineLength, colourBoxThickness);
	
	ofSetColor(activeGraph->col1[0], activeGraph->col1[1], activeGraph->col1[2], activeGraph->col1[3]);
	ofRect(ofGetWidth() - xMargin - lineLength, yMargin + topColourBoxXOffset, lineLength, colourBoxThickness);

	ofSetColor(activeGraph->col1[0], activeGraph->col1[1], activeGraph->col1[2], activeGraph->col1[3]);
	ofRect(ofGetWidth() - xMargin - lineLength, ofGetHeight() - yMargin - yMarginBottomOffset + bottomColourBoxXOffset, lineLength, colourBoxThickness);

	ofPopStyle();
}



void Scene::addNewData(vector<DataObject> newData)
{
	barGraph.addNewData(newData);
	bodyGraph.addNewData(newData);
	
	tlStr = newData[0].info + "\n" + ofToString(newData[0].value);
	trStr = newData[1].info + "\n" + ofToString(newData[1].value);

	millisAtLastData = ofGetElapsedTimeMillis();
}


void Scene::keyPressed(int key)
{

}