#ifndef mitm_hpp
#define mitm_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "ofxJSON.h"

class Mitm {
    
private:
    const std::string kUserId = "11664553";
    const std::string kBearerToken = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOjExNjY0NTUzLCJ1c2VybmFtZSI6InRydW1wZnRxIiwiYXZhdGFyVXJsIjoiczM6Ly9oeXBlc3BhY2UtcXVpei9kZWZhdWx0X2F2YXRhcnMvVW50aXRsZWQtMV8wMDAxX2JsdWUucG5nIiwidG9rZW4iOm51bGwsInJvbGVzIjpbXSwiY2xpZW50IjoiIiwiZ3Vlc3RJZCI6bnVsbCwidiI6MSwiaWF0IjoxNTE5NTEyMTEyLCJleHAiOjE1MjcyODgxMTIsImlzcyI6Imh5cGVxdWl6LzEifQ.YxOrP_MnZTapJq5kZSmDd3MzG07W8ZeHcluI2l4cZWI";
    
    std::string url_;
    std::string socket_url_;
    bool connected_;
    std::string latest_message_;
    std::map<std::string, std::string> broadcast_headers_;
    std::map<std::string, std::string> socket_headers_;
    
    void SetHeader(std::map<std::string, std::string> map, std::string key, std::string value);
    std::vector<std::string> GetHeaderKeys(std::map<std::string, std::string> map);
    std::vector<std::string> GetHeaderValues(std::map<std::string, std::string> map);
    
public:
    void SetupBroadcast(std::string url);
    ofxJSONElement EmulatePhoneConnection();
    std::string ProcessSocketUrl(std::string url);
    
    void SetBroadcastHeader(std::string key, std::string value);
    std::vector<std::string> GetBroadcastHeaderKeys();
    std::vector<std::string> GetBroadcastHeaderValues();
    void SetSocketHeader(std::string key, std::string value);
    std::vector<std::string> GetSocketHeaderKeys();
    std::vector<std::string> GetSocketHeaderValues();
    
    bool IsConnected();
    void SetConnected(bool connected);
    std::string GetLatestMessage();
    void SetLatestMessage(std::string message);
};

#endif /* mitm_hpp */
