#ifndef bridge_hpp
#define bridge_hpp

#include <stdio.h>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>
#include "ofxJSON.h"
#include "utility.hpp"

using std::string;
using std::chrono::duration;
using std::chrono::high_resolution_clock;
using time_point = std::chrono::high_resolution_clock::time_point;

class Bridge {

private:
    time_point last_read_time_;
    time_point current_time_;
    int time_interval_ = 1000;
    string current_bridge_content_;
    
    string question_;
    vector<string> answers_;

public:
    /**
     * Initialize the Bridge to check for updated data from master
     */
    void Init();
    
    /**
     * Check if the Bridge has new content, and enforce a time interval
     *
     * @return if the Bridge is new
     */
    bool CheckBridgeReady();

    /**
     * Check the content of the Bridge
     *
     * @return if the Bridge content is different than the last one
     */
    bool CheckBridge();

    /**
     * Get the contents of the Bridge
     *
     * @return the string content of the Bridge
     */
    string GetBridgeContents();
    
    /**
     * Process the Bridge JSON file
     *
     * @param json the JSON element to process
     */
    void ProcessJson(ofxJSONElement &json);
    
    /* GETTERS AND SETTERS */
    
    string &GetQuestion();
    
    vector<string> &GetAnswers();
};

#endif /* bridge_hpp */
