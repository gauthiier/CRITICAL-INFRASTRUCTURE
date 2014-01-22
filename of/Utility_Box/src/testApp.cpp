#include "testApp.h"

// TODO
// ====
// - Add data points to graph as they arrive instead of at fixed points
// - Animate new values
// - Colour range - tween between 2 points
// 
//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(30);
	ofSetLogLevel(OF_LOG_SILENT);
	ofSetWindowPosition(0, 100);
	ofEnableSmoothing();
	ofSeedRandom(ofRandom(23243));
	ofSetFullscreen(true);
	ofSetVerticalSync(true);

	dataManager.setup();
	scene.setup();
	gui.setup();
	scene.graphManager.updateInfoText();
	scene.setupTitleFbo();

	isPaused = false;
}


void testApp::update()
{
	if (isPaused) return;

	dataManager.update();
	scene.update();

	if(gui.isVisible) 
		ofShowCursor();
	else 
		ofHideCursor();
}


void testApp::draw()
{
    dataManager.draw();
	scene.draw();
}


void testApp::mousePressed(int x, int y, int button)
{

}


void testApp::keyPressed(int key)
{
	if (key == 'p')
		isPaused = !isPaused;
	else if (key == 'f')
		ofToggleFullscreen();
	else if (key == 'c')
		scene.clearGraphData();
	else if (key == 't')
		scene.graphManager.updateInfoText();
	else if (key == 'o')
		scene.graphManager.outputData();

	scene.keyPressed(key);
}


void testApp::windowResized(int w, int h)
{
	scene.setViewport();
}