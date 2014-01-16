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
	void addGraphTextGUI();
	void addLegendTextGUI();
	void addGraphSimulationGUI();
	void addCameraGUI();
    void addVariousGUI();
    
    void variousGUIEvent(ofxUIEventArgs &e);
	void graphTextGUIEvent(ofxUIEventArgs &e);


    
    testApp* app;
	vector<string> publishers; 

};