//
//  gui->cpp
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#include "GUI.h"
#include "testApp.h"
#include "AbstractGraph.h"

void GUI::setup()
{
    app = (testApp*)ofGetAppPtr();
    GUIManager::setup();
    
    dim = 8;
	
    addKeyboardShortcutsGUI();
	addGraphGlobalGUI();
	addBarGraphDesignGUI();
	addBodyGraphDesignGUI();
	addGraphSimulationGUI();
    addBackgroundGUI();
	addHUDTextGUI();
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

    
    finaliseCanvas(gui, true);
}


void GUI::addGraphGlobalGUI()
{
	string title = "GRAPH GLOBAL";
    ofxUICanvas* gui = getNewGUI(title);

	vector<string> graphNames;
	graphNames.push_back("Bar graph");
	graphNames.push_back("Solid Body graph");
	graphNames.push_back("Line fade graph");

	gui->addRadio("Graph Selection", graphNames, OFX_UI_ORIENTATION_VERTICAL, dim*2, dim*2);
	
	gui->addSpacer(length, 1);
	gui->addRangeSlider("Graph X begin/end (percent)", 0, 1, &AbstractGraph::minGraphPercent, &AbstractGraph::maxGraphPercent, length, dim);
	

    ofAddListener(gui->newGUIEvent, this, &GUI::graphGlobalGUIEvent);
    finaliseCanvas(gui, true);
}



void GUI::addBarGraphDesignGUI()
{
	string title = "BAR GRAPH DESIGN";
    ofxUICanvas* gui = getNewGUI(title);
	
	gui->addSlider("Graph Item X Gap", 5, 50, &app->scene.barGraph.graphItemXGap, length, dim);
	gui->addSlider("BarWidth", 2, 50, &app->scene.barGraph.barWidth, length, dim);
	gui->addSlider("Graph Height Max", 100, 1000, &app->scene.barGraph.graphHeightMax, length, dim);
	gui->addSlider("Data send speed (seconds)", 0.1, 20, &app->scene.barGraph.sendDataSpeed, length, dim);
	
	gui->addSpacer(length, 1);
	gui->addSlider("Data0 red", 0, 255, &app->scene.barGraph.col0[0], length, dim);
	gui->addSlider("Data0 green", 0, 255, &app->scene.barGraph.col0[1], length, dim);
	gui->addSlider("Data0 blue", 0, 255, &app->scene.barGraph.col0[2], length, dim);
	gui->addSlider("Data0 alpha", 0, 255, &app->scene.barGraph.col0[3], length, dim);

	gui->addSpacer(length, 1);
	gui->addSlider("Data1 red", 0, 255, &app->scene.barGraph.col1[0], length, dim);
	gui->addSlider("Data1 green", 0, 255, &app->scene.barGraph.col1[1], length, dim);
	gui->addSlider("Data1 blue", 0, 255, &app->scene.barGraph.col1[2], length, dim);
	gui->addSlider("Data1 alpha", 0, 255, &app->scene.barGraph.col1[3], length, dim);

    finaliseCanvas(gui, true);
}


void GUI::addBodyGraphDesignGUI()
{
	string title = "BODY GRAPH DESIGN";
    ofxUICanvas* gui = getNewGUI(title);
	
	gui->addToggle("Toggle Draw Body", &app->scene.bodyGraph.isDrawBody, toggleDim, toggleDim);
	gui->addToggle("Toggle Draw Lines", &app->scene.bodyGraph.isDrawLines, toggleDim, toggleDim);
	gui->addSlider("Graph Item X Gap", 5, 50, &app->scene.bodyGraph.graphItemXGap, length, dim);
	gui->addSlider("Line width", 1, 50, &app->scene.bodyGraph.lineWidth, length, dim);
	gui->addSlider("Graph Height Max", 100, 1000, &app->scene.bodyGraph.graphHeightMax, length, dim);
	gui->addSlider("Data send speed (seconds)", 0.1, 20, &app->scene.bodyGraph.sendDataSpeed, length, dim);
	
	gui->addSpacer(length, 1);
	gui->addSlider("Data0 red", 0, 255, &app->scene.bodyGraph.col0[0], length, dim);
	gui->addSlider("Data0 green", 0, 255, &app->scene.bodyGraph.col0[1], length, dim);
	gui->addSlider("Data0 blue", 0, 255, &app->scene.bodyGraph.col0[2], length, dim);
	gui->addSlider("Data0 alpha", 0, 255, &app->scene.bodyGraph.col0[3], length, dim);

	gui->addSpacer(length, 1);
	gui->addSlider("Data1 red", 0, 255, &app->scene.bodyGraph.col1[0], length, dim);
	gui->addSlider("Data1 green", 0, 255, &app->scene.bodyGraph.col1[1], length, dim);
	gui->addSlider("Data1 blue", 0, 255, &app->scene.bodyGraph.col1[2], length, dim);
	gui->addSlider("Data1 alpha", 0, 255, &app->scene.bodyGraph.col1[3], length, dim);

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


void GUI::addBackgroundGUI()
{
    string title = "BACKGROUND";
    ofxUICanvas* gui = getNewGUI(title);

	gui->addToggle("Toggle Video Visibility", &app->scene.isVideoVisible, toggleDim, toggleDim);
	gui->addToggle("Toggle Image Visibility", &app->scene.isImageVisible, toggleDim, toggleDim);
	gui->addSlider("Video/Image Width Percent", 0, 2, &app->scene.videoWidthPercentage, length, dim);
	gui->addSlider("Video/Image Height Percent", 0, 2, &app->scene.videoHeightPercentage, length, dim);

	

    gui->addLabel("VIDEO IMAGE SETTINGS");
	gui->addSlider("Brightness", 0, 2, &app->scene.brightness, length, dim);
	gui->addSlider("Contrast", 0, 2, &app->scene.contrast, length, dim);
	gui->addSlider("Saturation", 0, 2, &app->scene.saturation, length, dim);
	gui->addSlider("Red", 0, 2, &app->scene.red, length, dim);
	gui->addSlider("Green", 0, 2, &app->scene.green, length, dim);
	gui->addSlider("Blue", 0, 2, &app->scene.blue, length, dim);
	gui->addSlider("Alpha", 0, 2, &app->scene.alpha, length, dim);

	gui->addSpacer(length, 1);
    gui->addLabel("HUD BACKGROUND SETTINGS");
	gui->addSlider("Red .", 0, 255, &app->scene.hudColour[0], length, dim);
	gui->addSlider("Green .", 0, 255, &app->scene.hudColour[1], length, dim);
	gui->addSlider("Blue .", 0, 255, &app->scene.hudColour[2], length, dim);
	gui->addSlider("Alpha .", 0, 255, &app->scene.hudColour[3], length, dim);
	gui->addSlider("Hole Width Percent", 0, 2, &app->scene.hudHoleWidthPercentage, length, dim);
	gui->addSlider("Hole Height Percent", 0, 2, &app->scene.hudHoleHeightPercentage, length, dim);
	gui->addSlider("Circle Point Size", 0, 100, &app->scene.circlePointSize, length, dim);

    ofAddListener(gui->newGUIEvent, this, &GUI::variousGUIEvent);
    finaliseCanvas(gui, true);
}


void GUI::addHUDTextGUI()
{
    string title = "HUD TEXT";
    ofxUICanvas* gui = getNewGUI(title);
	
	gui->addSlider("X Margin", 0, 500, &app->scene.xMargin, length, dim);
	gui->addSlider("Y Margin", 0, 500, &app->scene.yMargin, length, dim);
	gui->addSlider("Y Margin Bottom Offset", 0, 300, &app->scene.yMarginBottomOffset, length, dim);
	gui->addSlider("Line Length", 50, 500, &app->scene.lineLength, length, dim);
	gui->addSlider("Line Spacing", 0, 10, &app->scene.lineSpacing, length, dim);
	gui->addSlider("Text Size", 10, 100, &app->scene.textSize, length, dim);
	gui->addSlider("Value average amount", 2, 150, &app->scene.averageAmount, length, dim);
	
	gui->addSpacer(length, 1);
	gui->addSlider("Red", 0, 255, &app->scene.textColour[0], length, dim);
	gui->addSlider("Green", 0, 255, &app->scene.textColour[1], length, dim);
	gui->addSlider("Blue", 0, 255, &app->scene.textColour[2], length, dim);
	gui->addSlider("Alpha", 0, 255, &app->scene.textColour[3], length, dim);
	
	gui->addSpacer(length, 1);
    gui->addLabel("COLOUR KEY");
	gui->addSlider("Top Colour Box X Offset", -300, 300, &app->scene.topColourBoxXOffset, length, dim);
	gui->addSlider("Bottom Colour Box X Offset", -300, 300, &app->scene.bottomColourBoxXOffset, length, dim);
	gui->addSlider("Colour Box Thickness", 1, 50, &app->scene.colourBoxThickness, length, dim);

    ofAddListener(gui->newGUIEvent, this, &GUI::variousGUIEvent);
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



void GUI::graphGlobalGUIEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
    
	if (name == "Bar graph")
    {
		//ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
		if (toggle->getValue()) app->scene.activeGraph = &app->scene.barGraph;
    }
    else if (name == "Solid Body graph")
    {
		printf("------------------- Solid Body graph\n");
		if (toggle->getValue()) app->scene.activeGraph = &app->scene.bodyGraph;
    }
    else if (name == "Line fade graph")
	{
		printf("------------------- Line fade graph\n");
		//app->scene.activeGraph = &app->scene.lineGraph;
    }
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