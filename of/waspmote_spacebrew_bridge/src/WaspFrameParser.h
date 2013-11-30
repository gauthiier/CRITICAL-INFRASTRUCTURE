//
//  WaspFrameParser.h
//  waspmote_gateway_parser
//
//  Created by dviid on 11/23/13.
//
//

#ifndef __waspmote_gateway_parser__WaspFrameParser__
#define __waspmote_gateway_parser__WaspFrameParser__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MIN_FRAME_ENTRIES   7

class WaspFrame {
    
public:
    
    WaspFrame(){;}
    
    string  serial_id;
    string  mote_id;
    int     frame_seq;
    string  mac;
    int     adc_data;
    int     battery_level;
        
    friend ostream& operator<<(ostream& os, const WaspFrame& wf);
    
};

class WaspFrameParser {
    
public:
    
    static void ASCII_split_frame(string &input, vector<string> &output);
    static void ASCII_token_frame(string &input, vector<string> &output);
    
    static void ASCII_process(string &input, vector<WaspFrame> &output);
    
    static string ASCII_parse(string id, string input);
    
};

#endif /* defined(__waspmote_gateway_parser__WaspFrameParser__) */
