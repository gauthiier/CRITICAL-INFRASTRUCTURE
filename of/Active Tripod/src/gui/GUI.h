//
//  GUI.h
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#pragma once

#include "ofMain.h"
#include "GUIManager.h"

class testApp;

class GUI : GUIManager
{
public:
    virtual void setup();
    virtual bool getVisible();
    
    void addKeyboardShortcutsGUI();
	void addGraphAnimationGUI();
	void addBarGraphDesignGUI();
	void addGraphSimulationGUI();
    void addBackgroundGUI();
    void addVariousGUI();
    
    void variousGUIEvent(ofxUIEventArgs &e);

    virtual void update();
    virtual void draw();
    
    testApp* app;
	vector<string> publishers; 
};