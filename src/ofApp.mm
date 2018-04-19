#include "ofApp.h"

const int kAnswerCount = 3;
const string kBroadcastUrl = "https://api-quiz.hype.space/shows/now?type=hq&userId=USER_ID";

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
const ofRectangle kAnswerBox((kWidth - kAnswerRectWidth) / 2,
                              kAnswerRectOffset,
                              kAnswerRectWidth,
                              kAnswerRectHeight);

/* SETUP */

//--------------------------------------------------------------
void ofApp::setup(){
    SetupGui();
    ofSetBackgroundColor(kBgColor);
    SetupMitm();
}

/**
 * Setup and load the gui resources like fonts and images
 */
void ofApp::SetupGui() {
    iphone_x_.load("images/iphone_x.png");
    iphone_x_connected_.load("images/iphone_x_cxn.png");
    
    cabin_.load("fonts/Cabin-Regular.ttf", kRegularSize);
    cabin_bold_.load("fonts/Cabin-Bold.ttf", kBoldSize);
}

/**
 * Setup the connection with HQ server using the MITM strategy
 */
void ofApp::SetupMitm() {
    mitm_.SetupConstantHeaders();
    mitm_.SetupBroadcast(kBroadcastUrl);
    
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

/**
 * Setup the Swift socket connection code using values retrieved from MITM
 */
void ofApp::SetupSwift() {
    SocketHandler.url = @(mitm_.GetSocketUrl().c_str());
    
    SocketHandler.custom_header_keys = ConvertStringVector(GetMapKeys(mitm_.GetSocketHeaders()));
    SocketHandler.custom_header_values = ConvertStringVector(GetMapValues(mitm_.GetSocketHeaders()));
    
    [SocketHandler connect];
}

/* UPDATE */

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
                mitm_.UpdateFromMessage(question_, answers_);
                
                // TODO: Search for values (Sleuth)
            }
        }
    }
}

/**
 * Get the latest message from the Swift socket
 */
string ofApp::GetLatestMessage() {
    string value = string([SocketHandler.latest_message UTF8String]);
    return value;
}

/* UPDATE */

//--------------------------------------------------------------
void ofApp::draw(){
    DrawQuestion();
    DrawAnswers();
    DrawStatusBar();
}

/**
 * Draw the question and question background
 */
void ofApp::DrawQuestion() {
    ofSetColor(kWhiteColor);
    ofDrawRectRounded(kQuestionBox, kQuestionRectRounding);
    
    ofSetColor(kTextColor);
    DrawTextCentered(question_, cabin_bold_, 0, kWidth / kQuestionOffsetFraction);
}

/**
 * Modifies the color scheme for the following answer depending on confidence level
 */
void ofApp::UpdateAnswerColors(double confidence) {
    if (ApproxEquals(confidence, max_confidence_)) {
        current_shape_color_ = kCorrectColor;
        current_text_color_ = kWhiteColor;
    } else {
        current_shape_color_ = kOutlineColor;
        current_text_color_ = kTextColor;
    }
}

/**
 * Draw the answer options and confidence levels
 */
void ofApp::DrawAnswers() {
    for (int i = 0; i < kAnswerCount; i++) {
        int y_offset = i * (kAnswerRectHeight + kAnswerRectPadding);
        
        ofSetColor(kOutlineColor);
        ofSetLineWidth(kAnswerLineWidth);
        ofNoFill();
        
        ofDrawRectRounded(kAnswerBox.getX(),
                          kAnswerBox.getY() + y_offset,
                          kAnswerBox.getWidth(),
                          kAnswerBox.getHeight(),
                          kAnswerRectRounding);
        
        ofFill();
        
        UpdateAnswerColors(confidences_[i]);
        
        ofSetColor(current_shape_color_);
        ofDrawRectRounded(kAnswerBox.getX(),
                          kAnswerBox.getY() + y_offset,
                          (int) (kAnswerBox.getWidth() * std::max(confidences_[i], min_confidence_)),
                          kAnswerBox.getHeight(),
                          kAnswerRectRounding);
        
        ofSetColor(current_text_color_);
        DrawTextVerticalCenter(answers_[i],
                               cabin_,
                               kAnswerBox.getX() + kQuestionRectBorderWidth,
                               kAnswerBox.getY() + kAnswerBox.getHeight() / 2 + y_offset);
    }
}

/**
 * Draw the overlay with the status bar and frame
 */
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

/**
 * Draw text vertically centered at the given x and y position
 */
void ofApp::DrawTextVerticalCenter(string text, ofTrueTypeFont &font, int x, int y) {
    ofRectangle box = font.getStringBoundingBox(text, x, y);
    font.drawString(text, x, y + box.getHeight() / 2);
}

/* OBJ-C++ UTILITIES */

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

/* EVENTS */

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
