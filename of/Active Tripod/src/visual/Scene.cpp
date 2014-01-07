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
}


void Scene::update()
{
	barGraph.update();
}


void Scene::draw()
{
	drawVideo();
	barGraph.draw();
	drawHUD();
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

void Scene::drawHUD()
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