#include "DataManager.h"
#include "testApp.h"
#include "Globals.h"

void DataManager::setup()
{
	app = (testApp*)ofGetAppPtr();

	ofFile file;
    if(file.open("c:\\CRITICAL_INFRASTRUCTURE_config.txt"))
    {
        ofBuffer buf = file.readToBuffer() ;
        file.close();
        string appIDStr = buf.getFirstLine();
		appId = ofToInt(appIDStr);
		printf("config loaded - appIDStr:%s\n", appIDStr.c_str());
        //string port = buf.getNextLine();
        publisher0Name = appIDStr + "_0";
        publisher1Name = appIDStr + "_1";
    }
	
	newData.resize(2);

	isPublisher0DataReceived = false;
	isPublisher1DataReceived = false;

	setupSpacebrew();
}


void DataManager::setupSpacebrew()
{
    string host = "54.200.6.109"; // Spacebrew::SPACEBREW_CLOUD; // "localhost";
	string name = "CRITTICAL INFRASTRUCTURE";
    string description = "Description goes here. Not sure why.";

    spacebrew.addSubscribe(publisher0Name, Spacebrew::TYPE_RANGE);
    spacebrew.addSubscribe(publisher1Name, Spacebrew::TYPE_RANGE);
    spacebrew.connect( host, name, description );
	
    // listen to spacebrew events
    Spacebrew::addListener(this, spacebrew);
}


void DataManager::update()
{
	if (isPublisher0DataReceived && isPublisher1DataReceived) 
	{
		isPublisher0DataReceived = false;
		isPublisher1DataReceived = false;

		// send a DataReceived event
		app->scene.barGraph.addNewData(newData);
	}


	if (isDataSimulated)
	{
		if (ofGetFrameNum() % (int)simulationSpeed == 0)
		{
			//newData[0] = (int)(ofNoise(newData.size() * 0.04, ofGetFrameNum() * 0.03, ofGetElapsedTimef() * 0.1) * 1000);
			newData[0] = (int)(ofNoise(newData.size() * perlinXScale, ofGetElapsedTimef() * perlinYScale) * 1000);
			newData[1] = (int)(ofNoise((newData.size() + 500) * perlinXScale, (ofGetElapsedTimef() + 1000) * perlinYScale) * 1000);
			app->scene.barGraph.addNewData(newData);
		}
	}
}


void DataManager::draw()
{
	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofCircle(sin(ofGetElapsedTimef() * 0.5) * 300 + 300, 100, 20);
	ofPopStyle();
}




void DataManager::onMessage( Spacebrew::Message & m )
{
    if (m.name == publisher0Name)
	{
		isPublisher0DataReceived = true;
		//printf("frameNum: %i, publisher0Name: %i \n", ofGetFrameNum(), m.valueRange());
		newData[0] = m.valueRange();
    }
    else if (m.name == publisher1Name)
	{
		isPublisher1DataReceived = true;
		//printf("frameNum: %i, publisher1Name: %i \n", ofGetFrameNum(), m.valueRange());
		newData[1] = m.valueRange();
    }
}