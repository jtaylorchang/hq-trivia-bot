#include "ofApp.h"

const int kWidth = 354;
const int kHeight = 768;
const int kBoldSize = 72;
const int kRegularSize = 24;
const int kQuestionOffsetFraction = -3;
const int kQuestionRectBorderWidth = 20;
const int kQuestionRectOffsetFraction = 10;
const int kQuestionRectHeightFraction = 3;
const int kQuestionRectRounding = 20;

const ofColor kWhiteColor(255, 255, 255);
const ofColor kBgColor(53, 57, 154);
const ofRectangle kQuestionBox(kQuestionRectBorderWidth,
                               kHeight / kQuestionRectOffsetFraction,
                               kWidth - 2 * kQuestionRectBorderWidth,
                               kHeight / kQuestionRectHeightFraction);

string prepared_payload = "";

void ofApp::SetupGui() {
    iphone_x_.load("images/iphone_x.png");
    iphone_x_connected_.load("images/iphone_x_cxn.png");
    
    cabin_.load("fonts/Cabin-Regular.ttf", kBoldSize);
    cabin_bold_.load("fonts/Cabin-Bold.ttf", kRegularSize);
}

void ofApp::SetupMitm() {
    mitm_.SetupBroadcast("https://api-quiz.hype.space/shows/now?type=hq&userId=11664553");
    mitm_.EmulatePhoneConnection();
    if (mitm_.GameIsActive()) {
        std::cout << "Game is active, preparing socket" << std::endl;
        mitm_.ExtractSocketUrl();
        SetupSwift();
    } else {
        std::cout << "Game is not active, try again later" << std::endl;
    }
}

void ofApp::SetupSwift() {
    SocketHandler.url = @(mitm_.GetSocketUrl().c_str());
    [SocketHandler connect];
}

string ofApp::GetLatestMessage() {
    string value = string([SocketHandler.latest_message UTF8String]);
    return value;
}


//--------------------------------------------------------------
void ofApp::setup(){
    SetupGui();
    ofSetBackgroundColor(kBgColor);
    SetupMitm();
}

//--------------------------------------------------------------
void ofApp::update(){
    string latest_message = GetLatestMessage();
    mitm_.SetConnected(SocketHandler.connected);
    if (!latest_message.empty()) {
        mitm_.SetLatestMessage(latest_message);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(kWhiteColor);
    ofDrawRectRounded(kQuestionBox, kQuestionRectRounding);
    
    ofSetColor(kBgColor);
    DrawTextCentered(question_, cabin_bold_, 0, kWidth / kQuestionOffsetFraction);
    
    ofSetColor(kWhiteColor);
    iphone_x_.update();
    if (mitm_.IsConnected()) {
        iphone_x_connected_.draw(0, 0, kWidth, kHeight);
    } else {
        iphone_x_.draw(0, 0, kWidth, kHeight);
    }
}

/**
 * Draw text centered with the given font and given offsets
 */
void ofApp::DrawTextCentered(string text, ofTrueTypeFont &font, int x, int y) {
    ofRectangle box = font.getStringBoundingBox(text, x, y);
    font.drawString(text, x + (kWidth - box.getWidth()) / 2, y + (kHeight - box.getHeight()) / 2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
