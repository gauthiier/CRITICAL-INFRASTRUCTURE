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
	text.loadFont("fonts/Roboto-Regular.ttf", 80);
	thinText.loadFont("fonts/Roboto-Light.ttf", 80);

	graphManager.setup();

	for (int i = 0; i < 3; i++)
	{
		Camera camera;
		camera.setup(i);
		cameras[i] = camera;
	}
	activeCamera = &cameras[0];

	isCamRotate = true;
	isCamAutoSwap = true;

	setViewport();
}


void Scene::setupTitleFbo()
{
	ofFbo::Settings settings;
	settings.width = 900;
	settings.height = 180;
	settings.internalformat = GL_RGBA;
	titleFbo.allocate(settings);

	targetImage.loadImage("images/TARGET_small_2.png");

	titleFbo.begin();
	ofClear(0, 0, 0, 0);
	
	ofPushStyle();
	ofSetColor(255, 255);
	thinText.setLineSpacing(legendTextSpacing);
	thinText.setLineLength(700);
	thinText.setSize(80);
	thinText.setAlignment(FTGL_ALIGN_LEFT);
	ofPushMatrix();
	ofTranslate(195, -10);
	ofRotateZ(90);
	targetImage.draw(20, 20, 165, 165);
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(200, 80);
	thinText.drawString("CRITICAL INFRASTRUCTURE", 0, 0);
	ofPopMatrix();
	ofPopStyle();

	titleFbo.end();
}


void Scene::update()
{
	if (isCamAutoSwap)
	{
		if (activeCamera->camID == 0)
		{
			if (ofRandom(1) < activeCamera->swapProbability && activeCamera->isReadyForSwap) 
				switchCamera();
		}
		else if (activeCamera->camID == 1)
		{
			if (ofRandom(1) < activeCamera->swapProbability && activeCamera->isReadyForSwap) 
				switchCamera();
		}
		else if (activeCamera->camID == 2)
		{
			if (ofRandom(1) < activeCamera->swapProbability && activeCamera->isReadyForSwap) 
				switchCamera();
		}
	}

	for (int i = 0; i < 3; i++)
		if (isCamRotate) cameras[i].update();

	graphManager.update(activeCamera->getPosition());
}


void Scene::draw()
{
	ofBackground(0);

	activeCamera->begin(viewport);
	
	ofPushMatrix();
	ofRotateZ(90);
	ofSetColor(gridCol[0], gridCol[1], gridCol[2], gridCol[3]);
	ofDrawGridPlane((int)gridScale, (int)gridTicks, false);
	ofPopMatrix();

	graphManager.draw();

	activeCamera->end();
	
	ofPushStyle();
	ofSetColor(255, 255);
	text.setLineSpacing(legendTextSpacing);
	text.setLineLength(legendTextLineLength);
	text.setSize(legendTextSize);
	text.setAlignment(FTGL_ALIGN_LEFT);
	string str;
	for (int i = 0; i < graphManager.graphs.size(); i++)
	{
		string newStr = ofToString(i) + " - " + graphManager.graphs[i]->info;
		str += newStr + "\n";
	}

	text.drawString(str, legendTextPoint.x, legendTextPoint.y);
	ofPopStyle();

	ofPushStyle();
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(ofGetWidth() - (titleFbo.getHeight() * titleScale), ofGetHeight());
	ofRotateZ(-90);
	ofScale(titleScale, titleScale);
	titleFbo.draw(0, 0);
	ofPopMatrix();
	ofPopStyle();
}



void Scene::setViewport()
{
	viewport = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
}



void Scene::addNewData(int i, DataObject newData)
{
	graphManager.addNewData(i, newData);
}


void Scene::keyPressed(int key)
{
	if (key == '1')
		activeCamera = &cameras[0];
	if (key == '2')
		activeCamera = &cameras[1];
	if (key == '3')
		activeCamera = &cameras[2];
	if (key == 'a')
		isCamRotate = !isCamRotate;
}


void Scene::clearGraphData()
{
	graphManager.clearGraphData();
}



void Scene::switchCamera()
{
	int newCamID;
	if (activeCamera->camID == 0)
		newCamID = (ofRandom(1) < 0.5) ? 1 : 2;
	if (activeCamera->camID == 1)
		newCamID = (ofRandom(1) < 0.5) ? 0 : 2;
	if (activeCamera->camID == 2)
		newCamID = (ofRandom(2) < 0.5) ? 0 : 1;

	activeCamera->deactivate();
	activeCamera = &cameras[newCamID];
	activeCamera->activate();
}