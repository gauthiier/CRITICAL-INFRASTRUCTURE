#pragma once

#include "ofMain.h"

#include "ofxSpacebrew.h"

#include "ofMain.h"
#include "ofxSpacebrew.h"

class testApp;

class DataManager
{

	public:
		void setup();
		void setupSpacebrew();
		void update();
		void draw();

		testApp* app;

		int appId;

        // create your spacebrew object
        Spacebrew::Connection spacebrew;
		
		string publisher0Name;
		string publisher1Name;

		vector<int> newData;

		bool isPublisher0DataReceived;
		bool isPublisher1DataReceived;

		bool isDataSimulated;
		float perlinXScale;
		float perlinYScale;
		float simulationSpeed;
    
        // listen to spacebrew Messages
        void onMessage( Spacebrew::Message & m );
};
