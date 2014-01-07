#pragma once

#include "ofMain.h"

#include "DataManager.h"
#include "Scene.h"
#include "GUI.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mousePressed(int x, int y, int button);
		void keyPressed(int key);
		void windowResized(int w, int h);

		DataManager dataManager;
		Scene scene;
		GUI gui;

		bool isPaused;
};
