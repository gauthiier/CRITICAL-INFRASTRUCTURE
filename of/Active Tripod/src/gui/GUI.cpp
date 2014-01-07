//
//  gui->cpp
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#include "GUI.h"
#include "testApp.h"

void GUI::setup()
{
    app = (testApp*)ofGetAppPtr();
    GUIManager::setup();
    
    dim = 8;
	
    addKeyboardShortcutsGUI();
	//addGraphAnimationGUI();
	addBarGraphDesignGUI();
	addGraphSimulationGUI();
    addBackgroundGUI();
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


void GUI::addGraphAnimationGUI()
{
	string title = "GRAPH ANIMATION";
    ofxUICanvas* gui = getNewGUI(title);

    finaliseCanvas(gui, true);
}


void GUI::addBarGraphDesignGUI()
{
	string title = "BAR GRAPH DESIGN";
    ofxUICanvas* gui = getNewGUI(title);
	
	gui->addSlider("Graph Item X Gap", 5, 50, &app->scene.barGraph.graphItemXGap, length, dim);
	gui->addSlider("BarWidth", 2, 50, &app->scene.barGraph.barWidth, length, dim);
	
	gui->addSlider("Data0 red", 0, 255, &app->scene.barGraph.col0[0], length, dim);
	gui->addSlider("Data0 green", 0, 255, &app->scene.barGraph.col0[1], length, dim);
	gui->addSlider("Data0 blue", 0, 255, &app->scene.barGraph.col0[2], length, dim);
	gui->addSlider("Data0 alpha", 0, 255, &app->scene.barGraph.col0[3], length, dim);
	gui->addSlider("Data1 red", 0, 255, &app->scene.barGraph.col1[0], length, dim);
	gui->addSlider("Data1 green", 0, 255, &app->scene.barGraph.col1[1], length, dim);
	gui->addSlider("Data1 blue", 0, 255, &app->scene.barGraph.col1[2], length, dim);
	gui->addSlider("Data1 alpha", 0, 255, &app->scene.barGraph.col1[3], length, dim);

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

    gui->addLabel("GRADIENT COLOUR");
	gui->addSpacer(length, 1);
	gui->addSlider("Start red", 0, 255, &app->scene.bgGradStartCol[0], length, dim);
	gui->addSlider("Start green", 0, 255, &app->scene.bgGradStartCol[1], length, dim);
	gui->addSlider("Start blue", 0, 255, &app->scene.bgGradStartCol[2], length, dim);
	gui->addSlider("Start alpha", 0, 255, &app->scene.bgGradStartCol[3], length, dim);
	gui->addSpacer(length, 1);
	gui->addSlider("End red", 0, 255, &app->scene.bgGradEndCol[0], length, dim);
	gui->addSlider("End green", 0, 255, &app->scene.bgGradEndCol[1], length, dim);
	gui->addSlider("End blue", 0, 255, &app->scene.bgGradEndCol[2], length, dim);
	gui->addSlider("End alpha", 0, 255, &app->scene.bgGradEndCol[3], length, dim);
	gui->addSpacer(length, 1);
    gui->addLabel("BACKGROUND IMAGE");
	gui->addSlider("Brightness", 0, 2, &app->scene.brightness, length, dim);
	gui->addSlider("Contrast", 0, 2, &app->scene.contrast, length, dim);
	gui->addSlider("Saturation", 0, 2, &app->scene.saturation, length, dim);
	gui->addSlider("Red", 0, 2, &app->scene.red, length, dim);
	gui->addSlider("Green", 0, 2, &app->scene.green, length, dim);
	gui->addSlider("Blue", 0, 2, &app->scene.blue, length, dim);
	gui->addSlider("Alpha", 0, 2, &app->scene.alpha, length, dim);

    
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




void GUI::update()
{
    
}


void GUI::draw()
{
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