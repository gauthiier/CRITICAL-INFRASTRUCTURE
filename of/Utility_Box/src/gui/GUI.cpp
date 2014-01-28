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
	addGraphColourGUI();
	addGraphTextGUI();
	addLegendTextGUI();
	addGraphSimulationGUI();
	addCameraGUI();
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
    gui->addLabel("'t' - REDRAW TEXT FBOS", OFX_UI_FONT_SMALL);
    gui->addLabel("'o' - OUTPUT GRAPH DATA TO TXT", OFX_UI_FONT_SMALL);
    gui->addLabel("'1-3' - CHANGE CURRENT CAMERA", OFX_UI_FONT_SMALL);
    gui->addLabel("'a' - TOGGLE AUTO ROTATE CAM", OFX_UI_FONT_SMALL);

    
    finaliseCanvas(gui, true);
}


void GUI::addGraphGlobalGUI()
{
	string title = "GRAPH GLOBAL";
    ofxUICanvas* gui = getNewGUI(title);
 //   gui->addLabel("GRAPH TEXT");
	
	gui->addSpacer(length, 1);
	gui->addSlider("Reconnect Frequency", 1000, 60000, &app->dataManager.reconnectFrequency, length, dim);


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
	
	gui->addToggle("Toggle Graph animation", &Graph::isAnimating, toggleDim, toggleDim);
	gui->addToggle("Toggle New Min/Max clear", &Graph::isClearOnNewMinMax, toggleDim, toggleDim);
	gui->addSpacer(length, 1);
	
	gui->addToggle("Toggle Draw Body", &Graph::isDrawBody, toggleDim, toggleDim);
	gui->addToggle("Toggle Draw Lines", &Graph::isDrawLines, toggleDim, toggleDim);
	gui->addToggle("Toggle Clamp Y Values", &Graph::isClampYValues, toggleDim, toggleDim);
	gui->addSlider("Graph Item X Gap", 0.1, 2, &Graph::graphItemXGap, length, dim);
	gui->addSlider("Graph z Range", 0, 200, &Graph::zRange, length, dim);
	gui->addSlider("Graph Width max", 1, 300, &Graph::maxGraphWidth, length, dim);
	gui->addSlider("Graph Height Max", 0, 100, &Graph::graphHeightMax, length, dim);
	gui->addSlider("Graph bottom end (percent)", 0, 20, &Graph::graphEndPercent, length, dim);
	gui->addSlider("Data send speed (seconds)", 0.01, 10, &app->dataManager.sendDataSpeed, length, dim);
	gui->addSlider("Line Thickness", 1, 20, &Graph::lineThickness, length, dim);

	gui->addLabel("GRID");
	gui->addSlider("Scale", 1, 200, &app->scene.gridScale, length, dim);
	gui->addSlider("Ticks", 1, 50, &app->scene.gridTicks, length, dim);
	gui->addSlider("Grid Red", 0, 255, &app->scene.gridCol[0], length, dim);
	gui->addSlider("Grid Green", 0, 255, &app->scene.gridCol[1], length, dim);
	gui->addSlider("Grid Blue", 0, 255, &app->scene.gridCol[2], length, dim);
	gui->addSlider("Grid Alpha", 0, 255, &app->scene.gridCol[3], length, dim);

    finaliseCanvas(gui, true);
}

void GUI::addGraphColourGUI()
{
	string title = "GRAPH COLOUR";
    ofxUICanvas* gui = getNewGUI(title);
		
	gui->addLabel("COLOUR");
	gui->addSlider("Front red", 0, 255, &Graph::colFront[0], length, dim);
	gui->addSlider("Front green", 0, 255, &Graph::colFront[1], length, dim);
	gui->addSlider("Front blue", 0, 255, &Graph::colFront[2], length, dim);
	gui->addSlider("Front alpha", 0, 255, &Graph::colFront[3], length, dim);
	gui->addSlider("Back red", 0, 255, &Graph::colBack[0], length, dim);
	gui->addSlider("Back green", 0, 255, &Graph::colBack[1], length, dim);
	gui->addSlider("Back blue", 0, 255, &Graph::colBack[2], length, dim);
	gui->addSlider("Back alpha", 0, 255, &Graph::colBack[3], length, dim);

    finaliseCanvas(gui, true);
}

void GUI::addGraphTextGUI()
{
	string title = "GRAPH TEXT";
    ofxUICanvas* gui = getNewGUI(title);
	
	//gui->addToggle("Toggle Draw Lines", &Graph::isDrawLines, toggleDim, toggleDim);
	gui->addSlider("Line Width", 10, 150, &Graph::lineLength, length, dim);
	gui->addSlider("Line Spacing", 10, 50, &Graph::lineSpacing, length, dim);
	gui->addSlider("Text Size", 10, 100, &Graph::textSize, length, dim);
	gui->addSlider("Text Fbo Width", 10, 200, &Graph::fboW, length, dim);
	gui->addSlider("Text Fbo Height", 10, 100, &Graph::fboH, length, dim);
	gui->addSlider("Text Draw Y", 0, 100, &Graph::textY, length, dim);
	gui->addSlider("Text X", -200, 200, &Graph::textPnt.x, length, dim);
	gui->addSlider("Text Y", -200, 200, &Graph::textPnt.y, length, dim);
	gui->addSlider("Text z Offset", -50, 50, &Graph::graphTextZOffset, length, dim);

	gui->addWidgetDown(new ofxUILabelButton(false, "UPDATE TEXT", OFX_UI_FONT_MEDIUM)); 
	
    ofAddListener(gui->newGUIEvent, this, &GUI::graphTextGUIEvent);
    finaliseCanvas(gui, true);
}


void GUI::addLegendTextGUI()
{
	string title = "TITLE AND LEGEND TEXT";
    ofxUICanvas* gui = getNewGUI(title);
	
	gui->addLabel("TITLE");
	gui->addSlider("Scale", 0.1, 2, &app->scene.titleScale, length, dim);

	gui->addLabel("LEGEND");
	gui->addSlider("Size", 10, 100, &app->scene.legendTextSize, length, dim);
	gui->addSlider("Spacing", 0, 10, &app->scene.legendTextSpacing, length, dim);
	gui->addSlider("Line Length", 20, 1000, &app->scene.legendTextLineLength, length, dim);
	gui->addSlider("X", 0, 500, &app->scene.legendTextPoint.x, length, dim);
	gui->addSlider("Y", 0, 500, &app->scene.legendTextPoint.y, length, dim);
	

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


void GUI::addCameraGUI()
{
	string title = "CAMERA";
    ofxUICanvas* gui = getNewGUI(title);
	
    gui->addToggle("Rotation", &app->scene.isCamRotate, toggleDim, toggleDim);
    gui->addToggle("Auto Camera Swap", &app->scene.isCamAutoSwap, toggleDim, toggleDim);
	for (int i = 0; i < 3; i++)
	{
		gui->addLabel("CAMERA " + ofToString(i));
		gui->addSlider("Cam" + ofToString(i) + " Distance", 10, 200, &app->scene.cameras[i].distance, length, dim);
		gui->addSlider("Cam" + ofToString(i) + " Y", 1, 150, &app->scene.cameras[i].positionVec.y, length, dim);
		gui->addSlider("Cam" + ofToString(i) + " Direction Point Y", 0, 150, &app->scene.cameras[i].lookAtVec.y, length, dim);
		gui->addSlider("Cam" + ofToString(i) + " Rotation Speed", -2, 2, &app->scene.cameras[i].rotSpeed, length, dim);
		gui->addSlider("Cam" + ofToString(i) + " Swap Probablity (per frame)", 0.001, 0.1, &app->scene.cameras[i].swapProbability, length, dim);
		gui->addSlider("Cam" + ofToString(i) + " Min Seconds Before Swapping", 0.5, 10, &app->scene.cameras[i].minSecondsBeforeSwapping, length, dim);
	}

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



void GUI::graphTextGUIEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
    
    if (name == "UPDATE TEXT")
		app->scene.graphManager.updateInfoText();
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