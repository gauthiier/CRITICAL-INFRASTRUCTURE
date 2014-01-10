#include "testApp.h"

// TODO
// ====
// - Add video camera feed
// - Add colour boxes to text
// - Make system to slow down data - The screen should show 15-20 minutes worth of data
// - Make 3rd graph - separate fade
// - Crosshairs in HUD
// - Create graph animation system
// - Create a single config file to be loaded from online location. It will contain IP address and host name
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

	scene.keyPressed(key);
}


void testApp::windowResized(int w, int h)
{
}