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
	ofBackgroundGradient(ofColor(bgGradStartCol[0], bgGradStartCol[1], bgGradStartCol[2], bgGradStartCol[3]), 
		ofColor(bgGradEndCol[0], bgGradEndCol[1], bgGradEndCol[2], bgGradEndCol[3]), 
		OF_GRADIENT_CIRCULAR);


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

	

	barGraph.draw();
}

