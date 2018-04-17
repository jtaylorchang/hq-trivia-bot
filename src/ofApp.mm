#include "ofApp.h"

/* GRAPHICS CONSTANTS AND MAGIC NUMBERS */

const ofColor kWhiteColor(255, 255, 255);
const ofColor kBgColor(71, 73, 160);
const ofColor kOutlineColor(227, 227, 227);
const ofColor kTextColor(51, 51, 59);
const ofColor kCorrectColor(81, 201, 148);

const int kWidth = 354;
const int kHeight = 768;
const int kBoldSize = 18;
const int kRegularSize = 14;

const int kQuestionOffsetFraction = -3;
const int kQuestionRectBorderWidth = 20;
const int kQuestionRectOffset = kHeight / 10;
const int kQuestionRectPadding = kHeight / 16;
const int kQuestionRectWidth = kWidth - 2 * kQuestionRectBorderWidth;
const int kQuestionRectHeight = (kHeight * 3) / 4 - 2 * kQuestionRectPadding;
const int kQuestionRectRounding = 20;

const int kAnswerRectPadding = 10;
const int kAnswerRectHeight = kHeight / 14;
const int kAnswerRectWidth = kWidth - 3 * kQuestionRectBorderWidth;
const int kAnswerRectOffset = kQuestionRectPadding + kQuestionRectHeight - (kAnswerRectHeight + kAnswerRectPadding) * 3;
const int kAnswerRectRounding = kAnswerRectHeight / 2;
const int kAnswerLineWidth = 2;

/* GRAPHICS OBJECTS */

const ofRectangle kQuestionBox((kWidth - kQuestionRectWidth) / 2,
                               kQuestionRectPadding,
                               kQuestionRectWidth,
                               kQuestionRectHeight);
const ofRectangle kAnswer1Box((kWidth - kAnswerRectWidth) / 2,
                              kAnswerRectOffset,
                              kAnswerRectWidth,
                              kAnswerRectHeight);
const ofRectangle kAnswer2Box((kWidth - kAnswerRectWidth) / 2,
                              kAnswerRectOffset + kAnswerRectHeight + kAnswerRectPadding,
                              kAnswerRectWidth,
                              kAnswerRectHeight);
const ofRectangle kAnswer3Box((kWidth - kAnswerRectWidth) / 2,
                              kAnswerRectOffset + (kAnswerRectHeight + kAnswerRectPadding) * 2,
                              kAnswerRectWidth,
                              kAnswerRectHeight);

string prepared_payload = "";

void ofApp::SetupGui() {
    iphone_x_.load("images/iphone_x.png");
    iphone_x_connected_.load("images/iphone_x_cxn.png");
    
    cabin_.load("fonts/Cabin-Regular.ttf", kRegularSize);
    cabin_bold_.load("fonts/Cabin-Bold.ttf", kBoldSize);
}

void ofApp::SetupMitm() {
    mitm_.SetupBroadcast("https://api-quiz.hype.space/shows/now?type=hq&userId=11664553");
    mitm_.EmulatePhoneConnection();
    if (mitm_.GameIsActive()) {
        std::cout << "Game is active, preparing socket" << std::endl;
        mitm_.ExtractSocketUrl();
        mitm_.SetupSocket();
        
        SetupSwift();
    } else {
        std::cout << "Game is not active, try again later" << std::endl;
    }
}

void ofApp::SetupSwift() {
    SocketHandler.url = @(mitm_.GetSocketUrl().c_str());
    
    SocketHandler.custom_header_keys = ConvertStringVector(GetMapKeys(mitm_.GetSocketHeaders()));
    SocketHandler.custom_header_values = ConvertStringVector(GetMapValues(mitm_.GetSocketHeaders()));
    
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
    bool connected = SocketHandler.connected;
    mitm_.SetConnected(connected);
    
    if (connected) {
        string latest_message = GetLatestMessage();
        
        if (!latest_message.empty()) {
            if (latest_message != mitm_.GetLatestMessage()) {
                std::cout << "Received new message:" << std::endl;
                std::cout << latest_message << std::endl;
                
                mitm_.SetLatestMessage(latest_message);
                mitm_.ParseMessage(question_, answer1_, answer2_, answer3_);
                
                // Search for values (Sleuth)
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    DrawQuestion();
    DrawAnswers();
    DrawStatusBar();
}

void ofApp::DrawQuestion() {
    ofSetColor(kWhiteColor);
    ofDrawRectRounded(kQuestionBox, kQuestionRectRounding);
    
    ofSetColor(kTextColor);
    DrawTextCentered(question_, cabin_bold_, 0, kWidth / kQuestionOffsetFraction);
}

void ofApp::UpdateAnswerColors(double confidence) {
    if (ApproxEquals(confidence, max_confidence_)) {
        current_shape_color_ = kCorrectColor;
        current_text_color_ = kWhiteColor;
    } else {
        current_shape_color_ = kOutlineColor;
        current_text_color_ = kTextColor;
    }
}

void ofApp::DrawAnswers() {
    ofSetColor(kOutlineColor);
    ofSetLineWidth(kAnswerLineWidth);
    ofNoFill();
    
    ofDrawRectRounded(kAnswer1Box, kAnswerRectRounding);
    ofDrawRectRounded(kAnswer2Box, kAnswerRectRounding);
    ofDrawRectRounded(kAnswer3Box, kAnswerRectRounding);
    
    ofFill();
    
    /* ANSWER 1 */
    
    UpdateAnswerColors(confidence1_);
    
    ofSetColor(current_shape_color_);
    ofDrawRectRounded(kAnswer1Box.getX(), kAnswer1Box.getY(), (int) (kAnswer1Box.getWidth() * std::max(confidence1_, min_confidence_)), kAnswer1Box.getHeight(), kAnswerRectRounding);
    
    ofSetColor(current_text_color_);
    DrawTextVerticalCenter(answer1_, cabin_, kAnswer1Box.getX() + kQuestionRectBorderWidth, kAnswer1Box.getY() + kAnswer1Box.getHeight() / 2);
    
    /* ANSWER 2 */
    
    UpdateAnswerColors(confidence2_);
    
    ofSetColor(current_shape_color_);
    ofDrawRectRounded(kAnswer2Box.getX(), kAnswer2Box.getY(), (int) (kAnswer2Box.getWidth() * std::max(confidence2_, min_confidence_)), kAnswer2Box.getHeight(), kAnswerRectRounding);
    
    ofSetColor(current_text_color_);
    DrawTextVerticalCenter(answer2_, cabin_, kAnswer2Box.getX() + kQuestionRectBorderWidth, kAnswer2Box.getY() + kAnswer1Box.getHeight() / 2);
    
    /* ANSWER 3*/
    
    UpdateAnswerColors(confidence3_);
    
    ofSetColor(current_shape_color_);
    ofDrawRectRounded(kAnswer3Box.getX(), kAnswer3Box.getY(), (int) (kAnswer3Box.getWidth() * std::max(confidence3_, min_confidence_)), kAnswer3Box.getHeight(), kAnswerRectRounding);
    
    ofSetColor(current_text_color_);
    DrawTextVerticalCenter(answer3_, cabin_, kAnswer3Box.getX() + kQuestionRectBorderWidth, kAnswer3Box.getY() + kAnswer1Box.getHeight() / 2);
}

void ofApp::DrawStatusBar() {
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

void ofApp::DrawTextVerticalCenter(string text, ofTrueTypeFont &font, int x, int y) {
    ofRectangle box = font.getStringBoundingBox(text, x, y);
    font.drawString(text, x, y + box.getHeight() / 2);
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

/**
 * Converts a vector of strings from C++ to an array of NSStrings in Objective-C
 */
id ofApp::ConvertStringVector(vector<string> string_vector) {
    // code derived from:
    // https://gist.github.com/jeremy-w/3777700
    id nsstring_array = [NSMutableArray new];
    
    for (string current_string : string_vector) {
        id nsstring = [NSString stringWithUTF8String:current_string.c_str()];
        [nsstring_array addObject:nsstring];
    }
    
    return nsstring_array;
}
