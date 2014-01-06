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

	barGraph.draw();
}

