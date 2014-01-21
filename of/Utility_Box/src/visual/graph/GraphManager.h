
#include "ofMain.h"
#include "DataManager.h"
#include "Graph.h"
#include "ofxFTGL.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 7500

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
	void addNewData(int i, DataObject newData);
	void clearGraphData();
	void updateInfoText();
	void outputData();
	
	vector<Graph*> graphs;
	vector<Graph*> reorderedGraphs;
	ofxFTGLSimpleLayout text;

	ofxOscSender sender;
};