//
//  WaspFrameParser.cpp
//  waspmote_gateway_parser
//
//  Created by dviid on 11/23/13.
//
//

#include "WaspFrameParser.h"

#define FRAME_DELIM "<=>"
#define FRAME_SEP '#'

#include <sstream>
#include <iostream>

ostream& operator<<(ostream& out, const WaspFrame& wf)
{
    out << "--- WaspFrame ---" << endl;
    out << "Serial Id: " << wf.serial_id << endl;
    out << "Mote Id: " << wf.mote_id << endl;
    out << "Frame Seq.: " << wf.frame_seq << endl;
    out << "MAC: " << wf.mac << endl;
    out << "ADC: " << wf.adc_data << endl;
    out << "BATT: " << wf.battery_level << endl;
    out << "-----------------" << endl;
    
    return out;
    
}

void WaspFrameParser::ASCII_split_frame(string &input, vector<string> &output)
{
    //cout << "PARSE: " << input << endl;
        
    string d = FRAME_DELIM;
    string token;
    size_t i, j = 0;

    
    // CASE A
    if((i = input.find(d)) == std::string::npos) {
        input.erase(0, input.length());
        return;
    }
    
    while((j = input.find(d)) != std::string::npos) {
        token = input.substr(0, j);
        
        //cout << "TOKEN: " << token << endl;
        
        output.push_back(string(token));
        
        input.erase(0, j + d.length());
        
        //cout << "NEXT: " << input << endl;
    }
    
}

void WaspFrameParser::ASCII_token_frame(string &input, vector<string> &output)
{
    //cout << endl << "frame -- " << input << endl;
    
    stringstream ss(input);
    string tok;
    while(getline(ss, tok, FRAME_SEP))
    {
        output.push_back(tok);
    }
}

void WaspFrameParser::ASCII_process(string &input, vector<WaspFrame> &output, bool emit)
{
    vector<string> r;
    WaspFrameParser::ASCII_split_frame(input, r);        
    
    for(int i = 0; i < r.size(); i++) {
        
        vector<string> t;
        WaspFrameParser::ASCII_token_frame(r[i], t);
        
        //cout << "SIZE:::" << t.size() << endl;
        
        if(t.size() < MIN_FRAME_ENTRIES) continue; // not valid frame        
        
        WaspFrame* wp = new WaspFrame();
        
        wp->serial_id = t[1];
        wp->mote_id = t[2];
        wp->frame_seq = atoi(t[3].c_str());
        wp->mac = t[4];
        wp->adc_data = atoi(WaspFrameParser::ASCII_parse(wp->mote_id + ":", t[5]).c_str());
        wp->battery_level = atoi(WaspFrameParser::ASCII_parse("BAT:", t[6]).c_str());
        
        //cout << (*wp) << endl;
        
        output.push_back(*wp);
        
        if(emit) {
            ofNotifyEvent(_frame_event, wp);
        }
            
    }
        
}

string WaspFrameParser::ASCII_parse(string id, string  input)
{
    size_t i;
    if((i = input.find(id)) != std::string::npos) {
        return input.substr(i + id.length(), input.length());
    }
    return "";
    
}


