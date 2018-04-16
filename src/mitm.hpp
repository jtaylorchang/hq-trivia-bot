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
using ofx::HTTP::GetRequest;
using ofx::HTTP::DefaultClient;
using ofx::HTTP::Context;
using ofx::HTTP::BaseResponse;

class Mitm {
    
private:
    // Courtesy of creators of HQuack:
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
     * Initializes the headers and sets the given url for the Broadcast connection
     *
     * @param url the url for the broadcast
     */
    void SetupBroadcast(string url);
    
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
    
    /**
     * Accepts a url and formats it into socket format
     *
     * @param url the url to format
     * @return the formatted url
     */
    string ProcessSocketUrl(string url);
    
    /**
     * Applys all the headers in a given header map to the given GetRequest
     *
     * @param request the request to apply headers to
     * @param headers the headers to apply
     */
    void ApplyHeaders(GetRequest &request, map<string, string> &headers);
    
    /* GETTERS AND SETTERS */
    
    bool IsConnected();
    void SetConnected(bool connected);
    string GetLatestMessage();
    void SetLatestMessage(string message);
    string GetSocketUrl();
};

#endif /* mitm_hpp */
