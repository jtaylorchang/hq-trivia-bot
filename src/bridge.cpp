#include "bridge.hpp"

const string kBridgePath = "../../../bridge.json";

/**
 * Initialize the Bridge to check for updated data from master
 */
void Bridge::Init() {
    last_read_time_ = high_resolution_clock::now();
    current_time_ = last_read_time_;
    current_bridge_content_ = ReadFileAsString(kBridgePath);
}

/**
 * Check if the Bridge has new content, and enforce a time interval
 */
bool Bridge::CheckBridgeReady() {
    current_time_ = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> passed_time = current_time_ - last_read_time_;
    if (passed_time.count() >= time_interval_) {
        // Ready to check again
        last_read_time_ = current_time_;
        return CheckBridge();
    }
    
    return false;
}

/**
 * Check the content of the Bridge
 */
bool Bridge::CheckBridge() {
    string bridge_content = GetBridgeContents();
    if (!bridge_content.empty()) {
        // Bridge has new content
        current_bridge_content_ = bridge_content;
        cout << "Loading new content from bridge" << endl;
        cout << current_bridge_content_ << endl;
        
        ofxJSONElement json(current_bridge_content_);
        ProcessJson(json);
        return true;
    }
    
    return false;
}

/**
 * Get the contents of the Bridge
 */
string Bridge::GetBridgeContents() {
    string content = ReadFileAsString(kBridgePath);
    if (current_bridge_content_ == content) {
        // Content has not changed
        return "";
    }
    
    return content;
}

/**
 * Process the Bridge JSON file
 */
void Bridge::ProcessJson(ofxJSONElement &json) {
    question_ = json["question"].asString();
    answers_.clear();
    answers_.push_back(json["answer1"].asString());
    answers_.push_back(json["answer2"].asString());
    answers_.push_back(json["answer3"].asString());
}

/* GETTERS AND SETTERS */

string &Bridge::GetQuestion() {
    return question_;
}

vector<string> &Bridge::GetAnswers() {
    return answers_;
}
