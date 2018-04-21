#include "mitm.hpp"

const int kAnswerCount = 3;

/* CONNECTIONS */

/**
 * Initializes the headers that apply to both the broadcast and the socket
 */
void Mitm::SetupConstantHeaders() {
    cout << "Setting cross headers" << endl;
    
    SetConstantHeader("x-hq-client", "iOS/1.3.2 b84");
    SetConstantHeader("Authorization", "Bearer " + kBearerToken);
    SetConstantHeader("x-hq-stk", "MQ==");
    SetConstantHeader("Host", "api-quiz.hype.space");
}

/**
 * Initializes the headers and sets the given url for the Broadcast connection
 */
void Mitm::SetupBroadcast(string url) {
    cout << "Preparing connection to: " << url << endl;
    
    url_ = Replace(url, "USER_ID", kUserId);
    cout << "Updated url with user ID: " << url_ << endl;
    cout << "Setting broadcast headers, user ID, bearer token" << endl;
    
    SetMapValue(broadcast_headers_, "Accept", "*/*");
    SetMapValue(broadcast_headers_, "User-Agent", "HQ/84 CFNetwork/897.15 Darwin/17.5.0");
    SetMapValue(broadcast_headers_, "Accept-Language", "en-us");
}

/**
 * Initializes the headers for the socket connection (handled in Swift)
 */
void Mitm::SetupSocket() {
    cout << "Preparing socket headers" << endl;
    
    SetMapValue(socket_headers_, "Connection", "Keep-Alive");
    SetMapValue(socket_headers_, "Accept-Encoding", "gzip");
    SetMapValue(socket_headers_, "User-Agent", "okhttp/3.8.0");
}

/**
 * Connects to the HQ server, establishes a connection and returns the JSON result
 */
void Mitm::EmulatePhoneConnection() {
    cout << "Emulating HQ client connection" << endl;
    
    DefaultClient client;
    Context context;
    BaseResponse response;
    GetRequest request(url_, Poco::Net::HTTPMessage::HTTP_1_1);
    
    ApplyHeaders(request, broadcast_headers_);
    
    // code based on example code for ofxHTTP library by Christopher Baker
    // https://github.com/bakercp/ofxHTTP
    try {
        string json_content;
        
        std::istream &response_stream = client.execute(request, response, context);
        Poco::StreamCopier::copyToString(response_stream, json_content);
        
        cout << "Received JSON content:" << endl;
        cout << json_content << endl;
        
        ofxJSONElement json(json_content);
        broadcast_json_ = json;
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
    socket_url_ = broadcast_json_["broadcast"]["socketUrl"].asString();
    cout << "Extracted unfiltered socket: " << socket_url_ << endl;
    
    socket_url_ = Replace(socket_url_, "https://", "wss://");
    cout << "Filtered socket: " << socket_url_ << endl;
}

/* HEADERS */

/**
 * Sets headers that apply to both the broadcast and the socket
 */
void Mitm::SetConstantHeader(string key, string value) {
    SetMapValue(broadcast_headers_, key, value);
    SetMapValue(socket_headers_, key, value);
}

/**
 * Applys all the headers in a given header map to the given GetRequest
 */
void Mitm::ApplyHeaders(GetRequest &request, map<string, string> &headers) {
    for (auto i = headers.begin(); i != headers.end(); i++) {
        request.set(i->first, i->second);
    }
}

/**
 * Parses the latest message from the given json and retrieves question and answer data
 */
void Mitm::ParseMessage(ofxJSONElement &json, string &question_dest, vector<string> &answers_dest) {
    string question;
    vector<string> answers;
    
    question = json["question"].asString();
    for (int i = 0; i < kAnswerCount; i++) {
        // TODO
        answers.push_back(json["answers"][i]["text"].asString());
    }
    
    if (question.empty()) {
        // No question was received
        return;
    }
    
    question_dest = question;
    answers_dest = answers;
}

/**
 * Parses the latest message from the socket and retrieves question and answer data
 */
void Mitm::UpdateFromMessage(string &question_dest, vector<string> &answers_dest) {
    ofxJSONElement json(latest_message_);
    ParseMessage(json, question_dest, answers_dest);
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
