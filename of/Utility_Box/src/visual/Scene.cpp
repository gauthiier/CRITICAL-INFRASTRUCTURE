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


void Scene::update()
{
	if (isCamAutoSwap)
	{
		if (activeCamera->camID == 0)
		{
			if (ofRandom(1) < activeCamera->swapProbability) 
				switchCamera();
		}
		else if (activeCamera->camID == 1)
		{
			if (ofRandom(1) < activeCamera->swapProbability) 
				switchCamera();
		}
		else if (activeCamera->camID == 2)
		{
			if (ofRandom(1) < activeCamera->swapProbability) 
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
		//if (ofGetFrameNum() % 30 == 0)
		//	printf("- str:%s\n- - - - - *** - - - - -\n", newStr.c_str());
	}
	//if (ofGetFrameNum() % 30 == 0)
	//{
	//	printf("\n\n\n\n");
	//		printf("str(all):%s\n- - - - - *** - - - - -\n", str.c_str());
	//	printf("\n\n\n\n");
	//}
	
	text.drawString(str, legendTextPoint.x, legendTextPoint.y);
	ofPopStyle();
}



void Scene::setViewport()
{
	viewport = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
}



void Scene::addNewData(vector<DataObject> newData)
{
	graphManager.addNewData(newData);
}


void Scene::keyPressed(int key)
{
	if (key == '1')
		activeCamera = &cameras[0];
	if (key == '2')
		activeCamera = &cameras[1];
	if (key == '3')
		activeCamera = &cameras[2];
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

	printf("************ changing cameras to %i ************** \n", newCamID);

	activeCamera = &cameras[newCamID];
}