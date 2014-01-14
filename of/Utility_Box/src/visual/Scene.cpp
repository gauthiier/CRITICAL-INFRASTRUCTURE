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
	graphManager.setup();
    camera.setDistance(100);
    text.loadFont("fonts/Roboto-Light.ttf", 8);
	setViewport();
}


void Scene::update()
{
	graphManager.update(camera.getPosition());
}


void Scene::draw()
{
	ofBackground(0);

	camera.begin(viewport);
	
	ofPushMatrix();
	ofRotateZ(90);
	ofSetColor(255, 100);
	ofDrawGridPlane(60, 10, false);
	ofPopMatrix();


	graphManager.draw();

	camera.end();
}



void Scene::setViewport()
{
	viewport = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
}



void Scene::addNewData(vector<DataObject> newData)
{
	graphManager.addNewData(newData);
	
	//tlStr = newData[0].info + "\n" + ofToString(newData[0].value);
	//trStr = newData[1].info + "\n" + ofToString(newData[1].value);

	//millisAtLastData = ofGetElapsedTimeMillis();
}


void Scene::keyPressed(int key)
{

}


void Scene::clearGraphData()
{
	graphManager.clearGraphData();
}