//
//  Bridge.cpp
//  waspmote_spacebrew_bridge
//
//  Created by dviid on 12/1/13.
//
//

#include "Bridge.h"

#define wasp_signature "usbserial"
#define wasp_baud 115200

bool Bridge::setup_spacebrew() {
    _sb_connection.connect(SPACEBREW_SERVER, "CRITTICAL INFRASTRUCTURE"); // blocking ??
    sleep(5);
    return _sb_connection.isConnected();
}

bool Bridge::setup_serial() {
    
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

void Bridge::update(){
    
    static vector<WaspFrame> r;
    r.clear();
    
    if(_serial.available() >= SERIAL_BUFFER_LEN) {
        _serial.readBytes(_buffer, SERIAL_BUFFER_LEN);
        _payload += string(_buffer, _buffer + SERIAL_BUFFER_LEN);
        
        _wp.ASCII_process(_payload, r, false);
        
        //LOOK up MAP !!!!!!!!!!!!!!
        
        for(int i = 0; i < r.size(); i++) {
            
            WaspFrame wf = r[i];
            
            map<string, Publisher*>::iterator it = _map.find(wf.mote_id);
            
            if(it == _map.end()) {
                
                Publisher* p = new Publisher(wf.mote_id, &_sb_connection);
                p->data(wf.adc_data, wf.battery_level, wf.frame_seq);
                _map[wf.mote_id] = p;                
                
            } else {
                
                Publisher* p = it->second;
                p->data(wf.adc_data, wf.battery_level, wf.frame_seq);
                
            }
        }
        
        
    }
    
}

Publisher::Publisher(string id, Spacebrew::Connection* sbc) : _id(id), _sb_connection(sbc), _current_seq(0), _is_publish_ready(false)
{
    cout << "NEW PUBLISHER -- " << id << endl;
    
    _ci_data_id = _id + "-DATA";
    _batt_data_id = _id + "-BATT";
    
    setup_spacebrew_publisher();
        
}

void Publisher::setup_spacebrew_publisher()
{
    if(!_is_publish_ready && _sb_connection->isConnected()) {
        // ADD PUBLISHER INFO -- 2 publishers per waspmote (DATA, BATT)
        _sb_connection->addPublish(_batt_data_id, "range");
        _sb_connection->addPublish(_ci_data_id, "range");
        _is_publish_ready = true;
    }    
}


void Publisher::data(int ci_data, int batt_data, int seq)
{
    
//    if(seq <= _current_seq) return;
//    else _current_seq= seq;

    _current_seq= seq;

    cout << "Publisher: " << _id << endl;
    cout << seq << " - " << ci_data << " - " << batt_data << endl;    
    
    if(_sb_connection->isConnected()) {
        if (!_is_publish_ready) {
            setup_spacebrew_publisher();
            sleep(1);
        }
        _sb_connection->sendRange(_ci_data_id, ci_data);
        _sb_connection->sendRange(_batt_data_id, batt_data);
    }
    
    if (_ci_data.size() >= SERIAL_BUFFER_LEN) _ci_data.pop_front();
    if (_batt_data.size() >= SERIAL_BUFFER_LEN) _batt_data.pop_front();
    
    _ci_data.push_back(ci_data);
    _batt_data.push_back(batt_data);
    
}



