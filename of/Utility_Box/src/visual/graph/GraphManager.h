
#include "ofMain.h"
#include "DataManager.h"
#include "Graph.h"
#include "ofxFTGL.h"

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
	void updateInfoText();
	void outputData();
	
	vector<Graph*> graphs;
	vector<Graph*> reorderedGraphs;
	ofxFTGLSimpleLayout text;
};