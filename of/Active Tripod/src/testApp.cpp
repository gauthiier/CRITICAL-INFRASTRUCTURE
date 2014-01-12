#include "testApp.h"

// TODO
// ====
// - If min or max values change - clear graph - ask bout this
// - Create a single config file to be loaded from online location. It will contain IP address and host name
// - Create graph animation system
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

	isPaused = false;
}


void testApp::update()
{
	if (isPaused) return;

	dataManager.update();
	scene.update();
	//if (gui.isVisible()) 
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

	scene.keyPressed(key);
}


void testApp::windowResized(int w, int h)
{
}