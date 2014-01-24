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
	separateBodyGraph.setup();

    text.loadFont("fonts/Roboto-Light.ttf", 8);

	//isTestScrambleMinMaxData = false;
	isClearOnNewMinMax = false;
}


void Scene::update()
{
	vidGrabber.update();
	
	activeGraph->update();
}


void Scene::draw()
{
	drawVideo();
	activeGraph->draw();
	drawGraphValues();
	drawCrosshairs();
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


void Scene::drawGraphValues()
{
	if (activeGraph->publisher0Data.size() < 2) return;

	ofPoint val0 = activeGraph->currentPub0Point;
	ofPoint val1 = activeGraph->currentPub1Point;

	if (activeGraph->graphName == "BODY" || activeGraph->graphName == "SEPARATE_BODY")
	{
		val0 = activeGraph->graphTextPnt0;
		val1 = activeGraph->graphTextPnt1;
	}
	
	string stringVal0 = reduceDecimalCount(activeGraph->publisher0Data.back().stringValue, valDecimalPoints0);
	string stringVal1 = reduceDecimalCount(activeGraph->publisher1Data.back().stringValue, valDecimalPoints1);

	ofPushStyle();
	text.setAlignment(FTGL_ALIGN_LEFT);
	ofSetColor(graphTextColour[0], graphTextColour[1], graphTextColour[2], graphTextColour[3]);
	text.setSize(graphTextSize);
	text.drawString(
		stringVal0 + " " + activeGraph->publisher0Data.back().unitMeasure, 
		val0.x + 10, 
		val0.y);
	text.drawString(
		stringVal1 + " " + activeGraph->publisher1Data.back().unitMeasure, 
		val1.x + 10, 
		val1.y);
	ofPopStyle();
}


void Scene::drawCrosshairs()
{
	ofPushStyle();
	ofSetLineWidth(crosshairLineWidth);
	ofSetColor(hudColour[0], hudColour[1], hudColour[2], crosshairAlpha);

	ofLine(ofGetWidth() * 0.5, 
		ofGetHeight() * 0.5 - ((ofGetHeight() * 0.5) * crosshairVertScale), 
		ofGetWidth() * 0.5, 
		ofGetHeight() * 0.5 + ((ofGetHeight() * 0.5) * crosshairVertScale)); // vert

	ofLine(ofGetWidth() * 0.5 - ((ofGetWidth() * 0.5) * crosshairHorizScale), 
		ofGetHeight() * 0.5, 
		ofGetWidth() * 0.5 + ((ofGetWidth() * 0.5) * crosshairHorizScale), 
		ofGetHeight() * 0.5); // horz

	ofCircle(ofGetWidth() * 0.5, ofGetHeight() * 0.5, crosshairCircleSize);
	ofPopStyle();
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
	text.setLineLength(lineLength);
    text.setLineSpacing(lineSpacing);
	text.setSize(textSize);

	drawTextBox(tlStr, "TOP LEFT");
	drawTextBox(trStr, "TOP RIGHT");
	
	vector<DataObject> *p0Data = &activeGraph->publisher0Data;
	vector<DataObject> *p1Data = &activeGraph->publisher1Data;
	

	if (activeGraph->publisher0Data.size() == 0) return;
	
	string stringVal0 = reduceDecimalCount(activeGraph->publisher0Data.back().stringValue, valDecimalPoints0);
	string stringVal1 = reduceDecimalCount(activeGraph->publisher1Data.back().stringValue, valDecimalPoints1);


	int amountToAverage = MIN(p0Data->size(), averageAmount);
	if (p0Data->size() > 2)
	{
		if (p0Data->back().longlongIntValue > 0)
		{
			long long int average0 = 0;
			for (int i = 0; i < amountToAverage; i++)
				average0 += p0Data->at(p0Data->size() - i - 1).value;
			average0 /= amountToAverage;
			
			string valueWithCommas = addCommasToNumberString(ofToString(average0));
			
			blStr = "Increase: " + ofToString(p0Data->back().value - p0Data->at(p0Data->size() - 2).value) + "\n" +
				"Current Value: " + stringVal0 + "\n" + 
				"Running average: " + reduceDecimalCount(valueWithCommas, valDecimalPoints0);
			drawTextBox(blStr, "BOTTOM LEFT");
		}
		else
		{
			float average0 = 0;
			for (int i = 0; i < amountToAverage; i++)
				average0 += p0Data->at(p0Data->size() - i - 1).value;
			average0 /= amountToAverage;
			
			string valueWithCommas = (average0 > 999) ? addCommasToNumberString(ofToString(average0)) : ofToString(average0);
			
			blStr = "Increase: " + ofToString(p0Data->back().value - p0Data->at(p0Data->size() - 2).value) + "\n" +
				"Current Value: " + stringVal0 + "\n" + 
				"Running average: " + reduceDecimalCount(valueWithCommas, valDecimalPoints0);
			drawTextBox(blStr, "BOTTOM LEFT");
		}


		if (p1Data->back().longlongIntValue > 0)
		{
			long long int average1 = 0;
			for (int i = 0; i < amountToAverage; i++)
				average1 += p1Data->at(p1Data->size() - i - 1).value;
			average1 /= amountToAverage;
			
			string valueWithCommas = addCommasToNumberString(ofToString(average1));
			
			brStr = "Increase: " + ofToString(p1Data->back().value - p1Data->at(p1Data->size() - 2).value) + "\n" +
				"Current Value: " + stringVal1 + "\n" + 
				"Running average: " + reduceDecimalCount(valueWithCommas, valDecimalPoints1);
			drawTextBox(brStr, "BOTTOM RIGHT");
		}
		else
		{
			float average1 = 0;
			for (int i = 0; i < amountToAverage; i++)
				average1 += p1Data->at(p1Data->size() - i - 1).value;
			average1 /= amountToAverage;
			
			string valueWithCommas = (average1 > 999) ? addCommasToNumberString(ofToString(average1)) : ofToString(average1);
			
			brStr = "Increase: " + ofToString(p1Data->back().value - p1Data->at(p1Data->size() - 2).value) + "\n" +
				"Current Value: " + stringVal1 + "\n" + 
				"Running average: " + reduceDecimalCount(valueWithCommas, valDecimalPoints1);
			drawTextBox(brStr, "BOTTOM RIGHT");
		}
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
	if (isClearOnNewMinMax)
	{
		if (barGraph.publisher0Data.size() > 0)
		{
			if (newData[0].min != barGraph.publisher0Data.back().min || 
				newData[0].max != barGraph.publisher0Data.back().max || 
				newData[1].min != barGraph.publisher1Data.back().min || 
				newData[1].max != barGraph.publisher1Data.back().max) 
			{
				barGraph.clear();
				bodyGraph.clear();
				separateBodyGraph.clear();
			}
		}
	}

	barGraph.addNewData(newData);
	bodyGraph.addNewData(newData);
	separateBodyGraph.addNewData(newData);
	
	tlStr = newData[0].info + "\n" + newData[0].unitMeasure + "\n" + reduceDecimalCount(ofToString(newData[0].stringValue), valDecimalPoints0);
	trStr = newData[1].info + "\n" + newData[1].unitMeasure + "\n" + reduceDecimalCount(ofToString(newData[1].stringValue), valDecimalPoints1);
}


void Scene::keyPressed(int key)
{
}


void Scene::clearGraphData()
{
	barGraph.clear();
	bodyGraph.clear();
	separateBodyGraph.clear();
}








string Scene::addCommasToNumberString(string num)
{
    string temp;
	string integral = num;
	string fractional;
    int decimalLocation = integral.find('.');

	if (decimalLocation != -1)
	{
		integral = integral.substr(0 , decimalLocation);
		fractional = integral.substr(decimalLocation);
	}
	else
	{
		integral = num;
		fractional = "";
	}

    int endstring = integral.length();
	int i;
    for(i = endstring - 3; i >= 0; i -= 3) {
        if (i > 0) {
            temp = ","+ integral.substr(i, 3) + temp;
        } else {
            temp = integral.substr(i, 3) + temp;
        }      
    }
    if (i < 0) {
        temp = integral.substr(0, 3+i) + temp;
    }
    return temp + fractional;
}


string Scene::reduceDecimalCount(string num, int maxDecimal)
{
	string temp;
	string integral = num;
	string fractional;
    int decimalLocation = integral.find('.');

	if (decimalLocation != -1)
	{
		integral = integral.substr(0, decimalLocation);
		fractional = num.substr(decimalLocation + 1);
		if (fractional.size() > maxDecimal) fractional = fractional.substr(0, maxDecimal);
		
		return integral + "." + fractional;
	}
	else
	{
		return num;
	}
}