//
//  Bridge.h
//  waspmote_spacebrew_bridge
//
//  Created by dviid on 12/1/13.
//
//

#ifndef __waspmote_spacebrew_bridge__Bridge__
#define __waspmote_spacebrew_bridge__Bridge__

#include <iostream>

#include "ofxSpacebrew.h"
#include "WaspFrameParser.h"

static const int MAX_CACHED_DATA = 50;
static const int SERIAL_BUFFER_LEN = 136;
static const std::string SPACEBREW_SERVER = "sandbox.spacebrew.cc";
//static const std::string SPACEBREW_SERVER = "localhost";

class Publisher
{
public:
    
    Publisher(string id, Spacebrew::Connection* sbc);
    
    void setup_spacebrew_publisher();
    
    void data(int ci_data, int batt_data, int seq);
    
    string _id;
    string _ci_data_id;
    string _batt_data_id;
    
    // cache
    deque<int>     _ci_data;
    deque<int>     _batt_data;
    int             _current_seq;
    
    // spacebrew connection
    Spacebrew::Connection* _sb_connection;
    bool _is_publish_ready;
    // - todo -
    
};

class Bridge
{
    
public:
    
    Bridge(){;}
    
    bool setup_spacebrew();
    
    bool setup_serial();
    
    void update(); // threadable
    
    // wasp frame cb
    void data(WaspFrame* wf);
    
    Publisher* newPublisher(string id);
    
    
    // serial interface
    ofSerial        _serial;
    bool            _serial_set;
    unsigned char   _buffer[SERIAL_BUFFER_LEN];
    string          _payload;
    
    WaspFrameParser _wp;
    
    // spacebrew interface
    
    // map of spacebrew publishers
    map<string, Publisher*> _map;
    
    Spacebrew::Connection _sb_connection;
};


#endif /* defined(__waspmote_spacebrew_bridge__Bridge__) */
