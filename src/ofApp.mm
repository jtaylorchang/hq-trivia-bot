#include "ofApp.h"

//SocketHandler *socket = [SocketHandler new];

void SetupSwift() {
    SocketHandler.url = @"wss://echo.websocket.org";
    [SocketHandler connect];
}

std::string GetLatestMessage() {
    std::string value = std::string([SocketHandler.latest_message UTF8String]);
    return value;
}


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    SetupSwift();
    mitm_.SetLatestMessage("Message pending");
}

//--------------------------------------------------------------
void ofApp::update(){
    std::string latest_message = GetLatestMessage();
    if (!latest_message.empty()) {
        mitm_.SetLatestMessage(latest_message);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    std::string value = mitm_.GetLatestMessage();
    ofDrawBitmapString(value, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    std::cout << "Sending key press: " << key << std::endl;
    NSString *message_to_send = @(std::to_string(key).c_str());
    SocketHandler.payload = message_to_send;
    [SocketHandler send];
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
