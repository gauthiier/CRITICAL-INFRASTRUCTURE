#include "testApp.h"

#include "WaspFrameParser.h"

#include <string>

#define wasp_signature "usbserial"
#define wasp_baud 115200


bool testApp::setup_serial() {
    
    //_serial.enumerateDevices();
    
    vector <ofSerialDeviceInfo> list = _serial.getDeviceList();
    
    for(int i = 0; i < list.size(); i++) {
        if (list[i].getDeviceName().find(wasp_signature) != std::string::npos) {
            _serial.setup(list[i].getDevicePath(), wasp_baud);
            return true;
        }
    }
    
    return false;
}

string wp_ascii_split(string input)
{
    
}

//--------------------------------------------------------------
void testApp::setup(){
    
    _serial_set = setup_serial();
}

//--------------------------------------------------------------
void testApp::update(){
    
    static vector<WaspFrame> r;
    r.clear();
    
    if(_serial.available() >= BUFFER_LEN) {
        _serial.readBytes(_buffer, BUFFER_LEN);
        _payload += string(_buffer, _buffer + BUFFER_LEN);
        
        WaspFrameParser::ASCII_process(_payload, r);
        for(int i = 0; i < r.size(); i++) {
            ofLog() << r[i] << endl;
        }
        
    }

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
