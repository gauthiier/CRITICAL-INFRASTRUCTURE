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
	void addGraphGlobalGUI();
	void addBarGraphDesignGUI();
	void addBodyGraphDesignGUI();
	void addSeparateBodyGraphDesignGUI();
	void addGraphSimulationGUI();
    void addVideoGUI();
    void addHUDGUI();
	void addHUDTextGUI();
    void addVariousGUI();
    
	void graphGlobalGUIEvent(ofxUIEventArgs &e);
    void variousGUIEvent(ofxUIEventArgs &e);


    
    testApp* app;
	vector<string> publishers; 
};