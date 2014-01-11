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

	//isPublisher0DataReceived = false;
	//isPublisher1DataReceived = false;

	setupSpacebrew();

	nextDataSendTime = 0.1;
}


void DataManager::setupSpacebrew()
{
    string host = "54.194.189.129"; // Spacebrew::SPACEBREW_CLOUD; // "localhost";
	string name = "CRITICAL INFRASTRUCTURE";
    string description = "Description goes here. Not sure why. Let me know if you see this and tell me if you need it";

	spacebrew.addSubscribe(publisher0Name, Spacebrew::TYPE_STRING);
	spacebrew.addSubscribe(publisher1Name, Spacebrew::TYPE_STRING);
    spacebrew.connect( host, name, description );
	
    // listen to spacebrew events
    Spacebrew::addListener(this, spacebrew);
}


void DataManager::update()
{

	if (isDataSimulated)
	{
		if (ofGetFrameNum() % (int)simulationSpeed == 0)
		{
			DataObject dataObject0;
			dataObject0.info = "Some text to describe the data\nSome more text\nOne more line";
			dataObject0.value = ofNoise(newData.size() * perlinXScale, ofGetElapsedTimef() * perlinYScale);
			dataObject0.min = 0;
			dataObject0.max = 1;
			
			//printf("dataObject0.value = %f \n", dataObject0.value);

			newData[0] = dataObject0;

			DataObject dataObject1;
			dataObject1.info = "Some descriptive text\nSome more\nLittle bit more\nLast one";
			dataObject1.value = ofNoise((newData.size() + 500) * perlinXScale, (ofGetElapsedTimef() + 1000) * perlinYScale);
			dataObject1.min = 0;
			dataObject1.max = 1;
			
			newData[1] = dataObject1;

			app->scene.activeGraph->addNewData(newData);
		}
	}
	else
	{
		/*if (isPublisher0DataReceived && isPublisher1DataReceived) 
		{
			isPublisher0DataReceived = false;
			isPublisher1DataReceived = false;
			app->scene.addNewData(newData);
		}*/

		//sendDataSpeed = app->scene.activeGraph->sendDataSpeed;
		if (ofGetElapsedTimef() >= nextDataSendTime + app->scene.activeGraph->sendDataSpeed)
		{
			nextDataSendTime += app->scene.activeGraph->sendDataSpeed;
			app->scene.addNewData(newData);
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
	printf("new message - %s\n", m.valueString().c_str());
	// split the formatted string into a list of different data types
	vector<string> data = explode(",", m.valueString());
    //for(int i = 0; i < data.size(); i++)
    //    cout <<i << " ["<< data[i] <<"] " <<endl;


	// make a new data object and add the different data sources to it
	DataObject dataObject;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].substr(0, 5) == "info:") 
		{
			printf("- - info = %s\n",  data[i].substr(5, -1).c_str());
			dataObject.info = data[i].substr(5, -1).c_str();
		}
		if (data[i].substr(0, 6) == "value:") 
		{
			printf("- - value = %s\n",  data[i].substr(6, -1).c_str());
			dataObject.value = ofToFloat(data[i].substr(6, -1).c_str());
		}
		if (data[i].substr(0, 4) == "min:") 
		{
			printf("- - min = %s\n",  data[i].substr(4, -1).c_str());
			dataObject.min = ofToFloat(data[i].substr(4, -1).c_str());
		}			
		if (data[i].substr(0, 4) == "max:") 
		{
			printf("- - max = %s\n",  data[i].substr(4, -1).c_str());
			dataObject.max = ofToFloat(data[i].substr(4, -1).c_str());
		}
	}


    if (m.name == publisher0Name)
	{
		//isPublisher0DataReceived = true;
		newData[0] = dataObject;
    }
    else if (m.name == publisher1Name)
	{
		//isPublisher1DataReceived = true;
		newData[1] = dataObject;
    }
}



vector<string> DataManager::explode(const string &delimiter, const string &str)
{
    vector<string> arr;

    int strleng = str.length();
    int delleng = delimiter.length();
    if (delleng==0)
        return arr;//no change

    int i=0;
    int k=0;
    while( i<strleng )
    {
        int j=0;
        while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
        if (j==delleng)//found delimiter
        {
            arr.push_back(  str.substr(k, i-k) );
            i+=delleng;
            k=i;
        }
        else
        {
            i++;
        }
    }
    arr.push_back(  str.substr(k, i-k) );
    return arr;
}