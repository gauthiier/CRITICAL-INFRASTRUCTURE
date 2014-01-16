#pragma once

#include "ofMain.h"

#include "ofxSpacebrew.h"

#include "ofMain.h"
#include "ofxSpacebrew.h"

class testApp;

struct DataObject
{
	string info;
	float value;
	string stringValue;
	long long int longlongIntValue;
	float min;
	float max;
	string unitMeasure;
};

class DataManager
{

	public:
		void setup();
		void setupSpacebrew();
		void update();
		void draw();
		vector<string> explode( const string &delimiter, const string &str);
		string addCommasToNumberString(string num);
		
        // listen to spacebrew Messages
        void onMessage( Spacebrew::Message & m );

		testApp* app;

		int appId;

        // create your spacebrew object
        Spacebrew::Connection spacebrew;
		
		string publisher0Name;
		string publisher1Name;

		vector<DataObject> newData;

		//bool isPublisher0DataReceived;
		//bool isPublisher1DataReceived;

		bool isDataSimulated;
		float perlinXScale;
		float perlinYScale;
		float simulationSpeed;

		float nextDataSendTime;
};
