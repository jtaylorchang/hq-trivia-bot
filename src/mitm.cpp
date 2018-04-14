#include "mitm.hpp"

/* CONNECTIONS */


void Mitm::SetupBroadcast(std::string url) {
    url_ = url;
    //std::replace(url_, "USER_ID", kUserId);
    SetBroadcastHeader("x-hq-client", "iOS/1.3.2 b84");
    SetBroadcastHeader("Authorization", "Bearer " + kBearerToken);
    SetBroadcastHeader("x-hq-stk", "MQ==");
    SetBroadcastHeader("Host", "api-quiz.hype.space");
    SetBroadcastHeader("Connection", "Keep-Alive");
    SetBroadcastHeader("User-Agent", "HQ/84 CFNetwork/897.15 Darwin/17.5.0");
    SetBroadcastHeader("Accept-Language", "en-us");
}

ofxJSONElement Mitm::EmulatePhoneConnection() {
    
}

std::string Mitm::ProcessSocketUrl(std::string url) {
    std::string socket_url = url;
    //std::replace(socket_url.begin(), socket_url.end(), "https", "wss");
    return socket_url;
}

/* HEADERS */

void Mitm::SetHeader(std::map<std::string, std::string> map, std::string key, std::string value) {
    map[key] = value;
}

std::vector<std::string> Mitm::GetHeaderKeys(std::map<std::string, std::string> map) {
    std::vector<std::string> keys;
    for (auto i = map.begin(); i != map.end(); i++) {
        keys.push_back(i->first);
    }
    
    return keys;
}

std::vector<std::string> Mitm::GetHeaderValues(std::map<std::string, std::string> map) {
    std::vector<std::string> values;
    for (auto i = map.begin(); i != map.end(); i++) {
        values.push_back(i->second);
    }
    
    return values;
}

void Mitm::SetBroadcastHeader(std::string key, std::string value) {
    SetHeader(broadcast_headers_, key, value);
}

std::vector<std::string> Mitm::GetBroadcastHeaderKeys() {
    return GetHeaderKeys(broadcast_headers_);
}

std::vector<std::string> Mitm::GetBroadcastHeaderValues() {
    return GetHeaderValues(broadcast_headers_);
}

void Mitm::SetSocketHeader(std::string key, std::string value) {
    SetHeader(socket_headers_, key, value);
}

std::vector<std::string> Mitm::GetSocketHeaderKeys() {
    return GetHeaderKeys(socket_headers_);
}

std::vector<std::string> Mitm::GetSocketHeaderValues() {
    return GetHeaderValues(socket_headers_);
}

/* GETTERS AND SETTERS */

bool Mitm::IsConnected() {
    return connected_;
}

void Mitm::SetConnected(bool connected) {
    connected_ = connected;
}

std::string Mitm::GetLatestMessage() {
    return latest_message_;
}

void Mitm::SetLatestMessage(std::string message) {
    latest_message_ = message;
}
