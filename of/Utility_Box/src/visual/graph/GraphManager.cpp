
#include "GraphManager.h"

void GraphManager::setup()
{
	for (int i = 0; i < 30; i++)
	{
		Graph *graph = new Graph(i);
		//graph.setup(i);
		graphs.push_back(graph);
	}
}


void GraphManager::update(ofVec3f ativeCamPos)
{
	for (int i = 0; i < graphs.size(); i++)
	{
		Graph *graph = graphs[i];
		graph->update(ativeCamPos);
	}

	std::sort(graphs.begin(), graphs.end(), compareGraphByDistToCam());
}


void GraphManager::draw()
{
	for (int i = 0; i < graphs.size(); i++)
	{
		Graph *graph = graphs[i];
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