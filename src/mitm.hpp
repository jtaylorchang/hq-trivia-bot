#ifndef mitm_hpp
#define mitm_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "ofxHTTP.h"
#include "ofxJSON.h"
#include "utility.hpp"

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using ofx::HTTP::GetRequest;
using ofx::HTTP::DefaultClient;
using ofx::HTTP::Context;
using ofx::HTTP::BaseResponse;

class Mitm {
    
private:
    // Courtesy of creators of HQuack (rather than use my own bearer token)
    const string kUserId = "11664553";
    const string kBearerToken = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOjExNjY0NTUzLCJ1c2VybmFtZSI6InRydW1wZnRxIiwiYXZhdGFyVXJsIjoiczM6Ly9oeXBlc3BhY2UtcXVpei9kZWZhdWx0X2F2YXRhcnMvVW50aXRsZWQtMV8wMDAxX2JsdWUucG5nIiwidG9rZW4iOm51bGwsInJvbGVzIjpbXSwiY2xpZW50IjoiIiwiZ3Vlc3RJZCI6bnVsbCwidiI6MSwiaWF0IjoxNTE5NTEyMTEyLCJleHAiOjE1MjcyODgxMTIsImlzcyI6Imh5cGVxdWl6LzEifQ.YxOrP_MnZTapJq5kZSmDd3MzG07W8ZeHcluI2l4cZWI";
    
    string url_;
    string socket_url_;
    bool connected_;
    string latest_message_;
    map<string, string> broadcast_headers_;
    map<string, string> socket_headers_;
    ofxJSONElement broadcast_json_;
    
public:
    /**
     * Initializes the headers that apply to both the broadcast and the socket
     */
    void SetupConstantHeaders();
    
    /**
     * Initializes the headers and sets the given url for the Broadcast connection
     *
     * @param url the url for the broadcast
     */
    void SetupBroadcast(string url);
    
    /**
     * Initializes the headers for the socket connection (handled in Swift)
     */
    void SetupSocket();
    
    /**
     * Connects to the HQ server, establishes a connection and saves the JSON result
     */
    void EmulatePhoneConnection();
    
    /**
     * Checks if the HQ game is live
     *
     * @return if the game is live
     */
    bool GameIsActive();
    
    /**
     * Pulls the socket url out of the broadcast object in the stream json
     */
    void ExtractSocketUrl();
    
    /* HEADERS */
    
    /**
     * Sets headers that apply to both the broadcast and the socket
     *
     * @param key the key of the header
     * @param value the value of the header
     */
    void SetConstantHeader(string key, string value);
    
    /**
     * Applys all the headers in a given header map to the given GetRequest
     *
     * @param request the request to apply headers to
     * @param headers the headers to apply
     */
    void ApplyHeaders(GetRequest &request, map<string, string> &headers);
    
    /* SOCKET CONNECTION */
    
    /**
     * Parses the latest message from the given json and retrieves question and answer data
     *
     * @param json the json to parse
     * @param question_dest the reference to the variables to store the question
     * @param answers_dest the reference to the variables to store the answer choices
     */
    void ParseMessage(ofxJSONElement &json, string &question_dest, vector<string> &answers_dest);
    
    /**
     * Uses the latest message from the socket to set the new question and answer values
     *
     * @param question_dest the reference to the variables to store the question
     * @param answers_dest the reference to the variables to store the answer choices
     */
    void UpdateFromMessage(string &question_dest, vector<string> &answers_dest);
    
    /* GETTERS AND SETTERS */
    
    bool IsConnected();
    void SetConnected(bool connected);
    string GetLatestMessage();
    void SetLatestMessage(string message);
    string GetSocketUrl();
    map<string, string> &GetSocketHeaders();
};

#endif /* mitm_hpp */
