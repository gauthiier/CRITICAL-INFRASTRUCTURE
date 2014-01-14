
#include "ofMain.h"
#include "DataManager.h"
#include "Graph.h"

struct compareGraphByDistToCam
{
	bool operator() (const Graph* lhs, const Graph* rhs) { return lhs->distToCam > rhs->distToCam; }
};

class GraphManager
{
public:
	void setup();
	void update(ofVec3f ativeCamPos);
	void draw();
	void addNewData(vector<DataObject> newData);
	void clearGraphData();

	vector<Graph*> graphs;
};