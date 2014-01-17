
#include "GraphManager.h"

void GraphManager::setup()
{
    text.loadFont("fonts/Roboto-Regular.ttf", 80);

	for (int i = 0; i < 30; i++)
	{
		Graph *graph = new Graph(i);
		graph->text = &text;
		graphs.push_back(graph);
		reorderedGraphs.push_back(graph);
	}

	sender.setup(HOST, PORT);
}



void GraphManager::update(ofVec3f ativeCamPos)
{
	for (int i = 0; i < graphs.size(); i++)
	{
		Graph *graph = graphs[i];
		graph->update(ativeCamPos);
	}

	ofxOscMessage m;
	m.setAddress("/utilityvalues");
	for (int i = 0; i < graphs.size(); i++)
	{
		m.addStringArg(graphs[i]->info);
		m.addFloatArg(graphs[i]->currentValue);
	}
	sender.sendMessage(m);

	std::sort(reorderedGraphs.begin(), reorderedGraphs.end(), compareGraphByDistToCam());
}



void GraphManager::draw()
{
	for (int i = 0; i < graphs.size(); i++)
	{
		Graph *graph = reorderedGraphs[i];
		graph->draw();
	}
}



void GraphManager::addNewData(vector<DataObject> newData)
{
	for (int i = 0; i < graphs.size(); i++)
	{
		Graph *graph = graphs[i];
		graph->addNewData(newData[i]);
	}
}



void GraphManager::clearGraphData()
{
	for (int i = 0; i < graphs.size(); i++)
	{
		Graph *graph = graphs[i];
		graph->clear();
	}
}


void GraphManager::updateInfoText()
{
	for (int i = 0; i < graphs.size(); i++)
	{
		Graph *graph = graphs[i];
		graph->setFboSettings();
		graph->drawInfoToFbo();
	}
}



void GraphManager::outputData()
{
	ofstream logFile;
	logFile.open(ofToDataPath("graph_log.txt").c_str());
	//ofstream	logFile( ofToDataPath("log.txt").c_str());

	string str;

	for (int i = 0; i < graphs.size(); i++)
	{
		Graph *graph = graphs[i];
		str += graph->publisher0Data[graph->publisher0Data.size() - 1].info + "\n";

		// print values
		str += "\nVALUES:\n\n";
		for (int j = 0; j < graph->publisher0Data.size(); j++)
			str += ofToString(j) + " = " + ofToString(graph->publisher0Data[j].value) + "\n";
		
		str += "\nMIN\n\n";
		for (int j = 0; j < graph->publisher0Data.size(); j++)
			str += ofToString(j) + " = " + ofToString(graph->publisher0Data[j].min) + "\n";
		
		str += "\nMAX\n\n";
		for (int j = 0; j < graph->publisher0Data.size(); j++)
			str += ofToString(j) + " = " + ofToString(graph->publisher0Data[j].max) + "\n";
		

		str += "\n\n\n\n";
	}




	unsigned char buf = ofToChar(str);
	// write data to txt file
	logFile << str[0] << str <<"\n";

	logFile.close();
}