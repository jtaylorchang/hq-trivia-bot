#include "mitm.hpp"

/* CONNECTIONS */

/**
 * Initializes the headers and sets the given url for the Broadcast connection
 */
void Mitm::SetupBroadcast(string url) {
    std::cout << "Preparing connection to: " << url << std::endl;
    std::cout << "Setting broadcast headers, user ID, bearer token" << std::endl;
    
    url_ = url;
    //std::replace(url_, "USER_ID", kUserId);
    SetMapValue(broadcast_headers_, "x-hq-client", "iOS/1.3.2 b84");
    SetMapValue(broadcast_headers_, "Authorization", "Bearer " + kBearerToken);
    SetMapValue(broadcast_headers_, "x-hq-stk", "MQ==");
    SetMapValue(broadcast_headers_, "Host", "api-quiz.hype.space");
    //SetMapValue(broadcast_headers_, "Connection", "Keep-Alive");
    SetMapValue(broadcast_headers_, "Accept", "*/*");
    SetMapValue(broadcast_headers_, "User-Agent", "HQ/84 CFNetwork/897.15 Darwin/17.5.0");
    SetMapValue(broadcast_headers_, "Accept-Language", "en-us");
}

/**
 * Initializes the headers for the socket connection (handled in Swift)
 */
void Mitm::SetupSocket() {
    SetMapValue(socket_headers_, "x-hq-client", "iOS/1.3.2 b84");
    SetMapValue(socket_headers_, "Authorization", "Bearer " + kBearerToken);
    SetMapValue(socket_headers_, "x-hq-stk", "MQ==");
    SetMapValue(socket_headers_, "Host", "api-quiz.hype.space");
    SetMapValue(socket_headers_, "Connection", "Keep-Alive");
    SetMapValue(socket_headers_, "Accept-Encoding", "gzip");
    SetMapValue(socket_headers_, "User-Agent", "okhttp/3.8.0");
}

/**
 * Connects to the HQ server, establishes a connection and returns the JSON result
 */
void Mitm::EmulatePhoneConnection() {
    std::cout << "Emulating HQ client connection" << std::endl;
    
    DefaultClient client;
    Context context;
    BaseResponse response;
    GetRequest request(url_, Poco::Net::HTTPMessage::HTTP_1_1);
    
    ApplyHeaders(request, broadcast_headers_);
    
    // code derived from ofxHTTP example code by Christopher Baker
    // https://github.com/bakercp/ofxHTTP
    try {
        string json_content;
        
        std::istream &response_stream = client.execute(request, response, context);
        Poco::StreamCopier::copyToString(response_stream, json_content);
        
        std::cout << "Received JSON content:" << std::endl;
        std::cout << json_content << std::endl;
        
        ofxJSONElement json(json_content);
        return json;
    } catch (const Poco::Exception &exception) {
        ofLogError("Mitm::EmulatePhoneConnection") << exception.displayText() << " " << exception.code();
    } catch (...) {
        ofLogError("Mitm::EmulatePhoneConnection") << "Got unknown exception.";
    }
    
    return ofxJSONElement();
}

/**
 * Checks if the HQ game is live
 */
bool Mitm::GameIsActive() {
    return (broadcast_json_["broadcast"] != broadcast_json_.null);
}

/**
 * Pulls the socket url out of the broadcast object in the stream json
 */
void Mitm::ExtractSocketUrl() {
    socket_url_ = broadcast_json_["broadcast"]["socket"].asString();
}

/**
 * Accepts a url and formats it into socket format
 */
string Mitm::ProcessSocketUrl(string url) {
    string socket_url = url;
    //std::replace(socket_url.begin(), socket_url.end(), "https", "wss");
    return socket_url;
}

/* HEADERS */

/**
 * Applys all the headers in a given header map to the given GetRequest
 */
void Mitm::ApplyHeaders(GetRequest &request, map<string, string> &headers) {
    for (auto i = headers.begin(); i != headers.end(); i++) {
        request.set(i->first, i->second);
    }
}

/**
 * Parses the latest message from the socket and retrieves question and answer data
 */
void Mitm::ParseMessage(string &question_dest, string &answer1_dest, string &answer2_dest, string &answer3_dest) {
    string question;
    string answer1;
    string answer2;
    string answer3;
    
    ofxJSONElement json(latest_message_);
    
    if (question.empty()) {
        return;
    }
    
    question_dest = question;
    answer1_dest = answer1;
    answer2_dest = answer2;
    answer3_dest = answer3;
}

/* GETTERS AND SETTERS */

bool Mitm::IsConnected() {
    return connected_;
}

void Mitm::SetConnected(bool connected) {
    connected_ = connected;
}

string Mitm::GetLatestMessage() {
    return latest_message_;
}

void Mitm::SetLatestMessage(string message) {
    latest_message_ = message;
}

string Mitm::GetSocketUrl() {
    return socket_url_;
}

map<string, string> &Mitm::GetSocketHeaders() {
    return socket_headers_;
}
