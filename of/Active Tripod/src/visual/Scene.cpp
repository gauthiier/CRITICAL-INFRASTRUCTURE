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
	bgImg.loadImage("images/tanks.jpg");
	rgbShader.load("shaders/RGBShader");
	barGraph.setup();


    text.loadFont("fonts/mplus-1c-regular.ttf", 8);
    //text.setLineLength(ofGetWidth() - margin * 2);


	xMargin = 500;
	yMargin = 400;
	lineLength = 200;
}


void Scene::update()
{
	barGraph.update();

	text.setLineLength(lineLength);
    text.setLineSpacing(lineSpacing);
	text.setSize(textSize);

}


void Scene::draw()
{
	drawVideo();
	barGraph.draw();
	drawHUDBG();
	drawHUDCopy();
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
	
    bgImg.draw(0, 0, ofGetWidth(), ofGetHeight());
	
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
	string tlStr = "TOP LEFT\nThis is some text\nthis is some more text\na little more";
	drawTextBox(tlStr, "TOP LEFT");
	string trStr = "TOP RIGHT\nThis is some text\nthis is some more text\na little more\none more line";
	drawTextBox(trStr, "TOP RIGHT");
	string blStr = "BOTTOM LEFT\nThis is some text\nthis is some more text";
	drawTextBox(blStr, "BOTTOM LEFT");
	string brStr = "BOTTOM RIGHT\nThis is some text\nthis is some more text\na little more";
	drawTextBox(brStr, "BOTTOM RIGHT");
}


void Scene::drawTextBox(string copy, string align)
{
	ofPushStyle();
	ofSetColor(textColour[0], textColour[1], textColour[2], textColour[3]);
	ofPushMatrix();
	if (align == "TOP LEFT")
	{
		ofTranslate(xMargin, yMargin);
		text.setAlignment(FTGL_ALIGN_LEFT);
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

	ofPopMatrix();
	ofPopStyle();
}



void Scene::keyPressed(int key)
{

}