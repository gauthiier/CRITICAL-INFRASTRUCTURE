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

class GUI : public GUIManager
{
public:
    virtual void setup();
    virtual bool getVisible();
    
    void addKeyboardShortcutsGUI();
	void addGraphGlobalGUI();
	void addGraphDesignGUI();
	void addGraphSimulationGUI();
    void addVariousGUI();
    
    void variousGUIEvent(ofxUIEventArgs &e);


    
    testApp* app;
	vector<string> publishers; 

};