#include "testApp.h"

// TODO
// ====
// - Make graph system with 3 simple (for now) but different graphs that can be interchanged
// - Make events system to send data to scene
// - 
// - 
// - Add to GUI
// - - Publisher choice
// - - IP address
// - - Host name
// - - App name
// 
// 
// 
// 
// 
// 
// 
// NOTES
// =====
// - Each publisher should have a unique number. There should be a config file kept in c:/ containing a unique ID
// - Check that the local data sources always have the same amount of data.



//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(30);
	ofSetLogLevel(OF_LOG_SILENT);
	ofSetWindowPosition(0, 100);
	ofEnableSmoothing();
	ofSeedRandom(ofRandom(23243));

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
void testApp::draw(){
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
	{
		isPaused = !isPaused;
	}
}