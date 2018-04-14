#include "ofApp.h"

std::string prepared_payload = "";

void ofApp::SetupMitm() {
    mitm_.SetupBroadcast("https://api-quiz.hype.space/shows/now?type=hq&userId=USER_ID");
}

void ofApp::SetupSwift() {
    SocketHandler.url = @"wss://ws-quiz.hype.space/ws/44451";
    [SocketHandler connect];
}

std::string ofApp::GetLatestMessage() {
    std::string value = std::string([SocketHandler.latest_message UTF8String]);
    return value;
}


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    SetupMitm();
    SetupSwift();
    mitm_.SetLatestMessage("Message pending");
}

//--------------------------------------------------------------
void ofApp::update(){
    std::string latest_message = GetLatestMessage();
    mitm_.SetConnected(SocketHandler.connected);
    if (!latest_message.empty()) {
        mitm_.SetLatestMessage(latest_message);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    std::string connection = "FALSE";
    if (mitm_.IsConnected()) {
        connection = "TRUE";
    }
    ofDrawBitmapString("Web Socket Connection: " + connection, 30, 30);
    
    ofDrawBitmapString("Sending: " + prepared_payload, 30, 45);
    
    std::string received_value = mitm_.GetLatestMessage();
    ofDrawBitmapString("Received: " + received_value, 30, 60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_RETURN) {
        NSString *message_to_send = @(prepared_payload.c_str());
        SocketHandler.payload = message_to_send;
        [SocketHandler send];
        prepared_payload.clear();
    } else {
        std::string key_str;
        key_str = char(key);
        prepared_payload.append(key_str);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
