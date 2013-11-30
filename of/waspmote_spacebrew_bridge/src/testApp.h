#pragma once

#include "ofMain.h"
#include "OfSerial.h"

#define BUFFER_LEN 136

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        bool setup_serial();
    
        string wp_ascii_split(string input);
    
    public:
    
        ofSerial    _serial;
        bool        _serial_set;
    
        unsigned char        _buffer[BUFFER_LEN];
        string      _payload;
    
		
};
