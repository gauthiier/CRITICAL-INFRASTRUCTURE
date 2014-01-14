//
//  gui->cpp
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#include "GUI.h"
#include "testApp.h"
#include "Graph.h"

void GUI::setup()
{
    app = (testApp*)ofGetAppPtr();
    GUIManager::setup();
    
    dim = 8;
	
    addKeyboardShortcutsGUI();
	addGraphGlobalGUI();
	addGraphDesignGUI();
	addGraphSimulationGUI();
    addVariousGUI();
    
    setGUIColour();
}


bool GUI::getVisible()
{
    return GUIManager::getVisible();
}



void GUI::addKeyboardShortcutsGUI()
{
    string title = "KEYBOARD SHORTCUTS";
    ofxUICanvas* gui = getNewGUI(title);

    gui->addLabel("SPACE - SHOW/HIDE GUI", OFX_UI_FONT_SMALL);
    gui->addLabel("'[' - PREVIOUS GUI", OFX_UI_FONT_SMALL);
    gui->addLabel("']' - NEXT GUI", OFX_UI_FONT_SMALL);
    gui->addLabel("'p' - TOGGLE PAUSE ANIMATION", OFX_UI_FONT_SMALL);
    gui->addLabel("'f' - TOGGLE FULLSCREEN", OFX_UI_FONT_SMALL);
    gui->addLabel("'c' - CLEAR ALL GRAPH DATA", OFX_UI_FONT_SMALL);

    
    finaliseCanvas(gui, true);
}


void GUI::addGraphGlobalGUI()
{
	string title = "GRAPH GLOBAL";
    ofxUICanvas* gui = getNewGUI(title);

	vector<string> graphNames;
	graphNames.push_back("Bar graph");
	graphNames.push_back("Solid Body graph");
	graphNames.push_back("Separate Body graph");

	gui->addRadio("Graph Selection", graphNames, OFX_UI_ORIENTATION_VERTICAL, dim*2, dim*2);
	
	gui->addSpacer(length, 1);
	gui->addRangeSlider("Graph X begin/end (percent)", 0, 1, &Graph::minGraphPercent, &Graph::maxGraphPercent, length, dim);
	
 //   gui->addLabel("GRAPH TEXT");
	//gui->addSpacer(length, 1);
	//gui->addSlider("Size", 5, 50, &app->scene.graphTextSize, length, dim);
	//gui->addSlider("Red", 0, 255, &app->scene.graphTextColour[0], length, dim);
	//gui->addSlider("Green", 0, 255, &app->scene.graphTextColour[1], length, dim);
	//gui->addSlider("Blue", 0, 255, &app->scene.graphTextColour[2], length, dim);
	//gui->addSlider("Alpha", 0, 255, &app->scene.graphTextColour[3], length, dim);

    finaliseCanvas(gui, true);
}



void GUI::addGraphDesignGUI()
{
	string title = "GRAPH DESIGN";
    ofxUICanvas* gui = getNewGUI(title);
	
	gui->addToggle("Toggle Draw Lines", &Graph::isDrawLines, toggleDim, toggleDim);
	gui->addSlider("Graph Item X Gap", 0.1, 2, &Graph::graphItemXGap, length, dim);
	gui->addSlider("Line width", 1, 20, &Graph::lineWidth, length, dim);
	gui->addSlider("Graph Width max", 1, 300, &Graph::maxGraphWidth, length, dim);
	gui->addSlider("Graph Height Max", 0, 100, &Graph::graphHeightMax, length, dim);
	gui->addSlider("Graph bottom end (percent)", 0, 20, &Graph::graphEndPercent, length, dim);
	gui->addSlider("Data send speed (seconds)", 0.1, 20, &app->dataManager.sendDataSpeed, length, dim);

	
	
	//gui->addSpacer(length, 1);
	//gui->addSlider("Data0 red", 0, 255, &app->scene.graphManager.col0[0], length, dim);
	//gui->addSlider("Data0 green", 0, 255, &app->scene.graph.col0[1], length, dim);
	//gui->addSlider("Data0 blue", 0, 255, &app->scene.graph.col0[2], length, dim);
	//gui->addSlider("Data0 alpha", 0, 255, &app->scene.graph.col0[3], length, dim);


    finaliseCanvas(gui, true);
}


void GUI::addGraphSimulationGUI()
{
	string title = "SIMULATION";
    ofxUICanvas* gui = getNewGUI(title);
	
    gui->addToggle("Toggle Data Simulation", &app->dataManager.isDataSimulated, toggleDim, toggleDim);
	gui->addSlider("Speed (data per frame)", 1, 60, &app->dataManager.simulationSpeed, length, dim);
	gui->addSlider("Perlin X Scale (data size)", 0.001, 0.5, &app->dataManager.perlinXScale, length, dim);
	gui->addSlider("Perlin Y Scale (time f)", 0.001, 0.5, &app->dataManager.perlinYScale, length, dim);

    finaliseCanvas(gui, true);
}




void GUI::addVariousGUI()
{
    string title = "VARIOUS";
    ofxUICanvas* gui = getNewGUI(title);

    //gui->addLabel("GRID");
    //gui->addToggle("GRID VISIBLE", &app->scene.isGridVisible, toggleDim, toggleDim);
    //gui->addSlider("GRID ALPHA", 0, 255, &app->scene.gridAlpha, length, dim);
    
    gui->addLabel("GUI DESIGN");
    gui->addSlider("RED", 0, 255, 255, length, dim);
    gui->addSlider("GREEN", 0, 255, 1, length, dim);
    gui->addSlider("BLUE", 0, 255, 1, length, dim);
    gui->addSlider("ALPHA", 0, 255, 255, length, dim);
    
    ofAddListener(gui->newGUIEvent, this, &GUI::variousGUIEvent);
    finaliseCanvas(gui, true);
}






void GUI::variousGUIEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    
    if (name == "RED")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        color.r = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "GREEN")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        color.g = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        color.b = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "ALPHA")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        color.a = slider->getScaledValue();
        setGUIColour();
    }
}