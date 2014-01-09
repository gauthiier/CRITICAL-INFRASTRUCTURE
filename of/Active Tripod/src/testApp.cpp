#include "testApp.h"

// TODO
// ====
// 
// - Map graph min/max
// - Stop graph going beyond 80% of the screen
// - Add separate colour sliders for body graph
// - In body graph use one long line instead of loads of lines
// - Make 2nd graph - body
// - Make 3rd graph - separate fade
// - Add colour boxes to text - DON'T use graph colours - add sliders
// - Crosshairs in HUD
// - Add video camera feed
// - Create text parsing system
// - Tidy up the first graph
// - Create animation system
// - Make system to slow down data - The screen should show 15-20 minutes worth of data
// - Create a single config file to be loaded from online location. It will contain IP address and host name
// 
// 
// 
// 
// NOTES
// =====
// - Check that the local data sources always have the same amount of data.



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

//--------------------------------------------------------------
void testApp::update()
{
	if (isPaused) return;

	dataManager.update();
	scene.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
    dataManager.draw();
	scene.draw();
}


//--------------------------------------------------------------
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