#include "DataManager.h"
#include "testApp.h"
#include "Globals.h"

void DataManager::setup()
{
	app = (testApp*)ofGetAppPtr();
	
	for (int i = 0; i < 30; i++)
	{
		DataObject dataObject;
		dataObject.value = -999;
		dataObject.min = -999;
		dataObject.max = -999;
		dataObject.info = "";
		newData.push_back(dataObject);
	}

	subscriberDevName = "dev2";  // dev2
	setupSpacebrew();
}


void DataManager::setupSpacebrew()
{
    string host = "54.194.189.129"; // Spacebrew::SPACEBREW_CLOUD; // "localhost";
	string name = "CRITICAL INFRASTRUCTURE UTILITY BOX" + subscriberDevName;
    string description = "Description goes here. Not sure why. Let me know if you see this and tell me if you need it";

	for (int i = 0; i < 30; i++)
	{
		spacebrew.addSubscribe("utility" + subscriberDevName + "_" + ofToString(i), Spacebrew::TYPE_STRING);
	}
	spacebrew.connect(host, name, description);
	
    // listen to spacebrew events
    Spacebrew::addListener(this, spacebrew);
}


void DataManager::update()
{
	if (isDataSimulated)
	{
		if (ofGetFrameNum() % (int)simulationSpeed == 0)
		{
			vector<DataObject> dataObjects;
			for (int i = 0; i < 30; i++)
			{
				DataObject dataObject;
				dataObject.info = "";
				dataObject.value = ofNoise(newData.size() * perlinXScale, (ofGetElapsedTimef() + (i * 756)) * perlinYScale);
				dataObject.min = 0;
				dataObject.max = 1;
			
				dataObjects.push_back(dataObject);
				app->scene.addNewData(i, dataObject);
			}

		}
	}
	else
	{
		//sendDataSpeed = app->scene.activeGraph->sendDataSpeed;
		if (ofGetElapsedTimef() >= nextDataSendTime + sendDataSpeed)
		{
			nextDataSendTime += sendDataSpeed;
			//app->scene.addNewData(newData);


			//ofstream logFile;
			//logFile.open(ofToDataPath("subscriber_log.txt").c_str());
			//string str;

			//for (int i = 0; i < newData.size(); i++)
			//{
			//	DataObject data = newData[i];
			//	str += ofToString(i) + " = " + data.info + "\n";
			//}
			//unsigned char buf = ofToChar(str);
			//// write data to txt file
			//logFile << str[0] << str <<"\n";

			//logFile.close();
		}
	}
}


void DataManager::draw()
{
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
			//printf("- info = %s\n",  data[i].substr(5, -1).c_str());
			dataObject.info = data[i].substr(5, -1).c_str();
		}
		if (data[i].substr(0, 6) == "value:") 
		{
			//printf("- - value = %s\n",  data[i].substr(6, -1).c_str());
			dataObject.value = ofToFloat(data[i].substr(6, -1).c_str());
		}
		if (data[i].substr(0, 4) == "min:") 
		{
			//printf("- - min = %s\n",  data[i].substr(4, -1).c_str());
			dataObject.min = ofToFloat(data[i].substr(4, -1).c_str());
		}			
		if (data[i].substr(0, 4) == "max:") 
		{
			//printf("- - max = %s\n",  data[i].substr(4, -1).c_str());
			dataObject.max = ofToFloat(data[i].substr(4, -1).c_str());
		}
	}


	for (int i = 0; i < 30; i++)
	{
		//printf("m.nme:%s, compare:%s \n", m.name.c_str(), ("utility" + subscriberDevName + "_" + ofToString(i)).c_str());
		if (m.name == "utility" + subscriberDevName + "_" + ofToString(i))
		{
			//isPublisher0DataReceived = true;
			newData[i] = dataObject;
			app->scene.addNewData(i, newData[i]);
			//printf("- - - adding %s to dataObject %i, info:%s, min:%f \n", m.name.c_str(), i, newData[i].info.c_str(), newData[i].min);
			
		}
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