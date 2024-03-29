#include "ofApp.h"

const int kHttpGood = 200;
const int kAnswerCount = 3;
const string kBroadcastUrl = "https://api-quiz.hype.space/shows/now?type=hq&userId=USER_ID";

/* GRAPHICS CONSTANTS AND MAGIC NUMBERS */

const int kTestArgCount = 2;
const int kTestArgIndex = 0;
const int kTestFileArgIndex = 1;
const int kMinArgCount = 3;
const int kQuestionArgIndex = 0;
const int kSlaveArgCount = 1;
const int kSlaveArgIndex = 0;

const int kQuestionLineWidth = 16;

const ofColor kWhiteColor(255, 255, 255);
const ofColor kBgColor(71, 73, 160);
const ofColor kOutlineColor(227, 227, 227);
const ofColor kTextColor(51, 51, 59);
const ofColor kCorrectColor(81, 201, 148);

const int kWidth = 354;
const int kHeight = 768;

const int kBoldSize = 18;
const int kRegularSize = 14;

const int kQuestionPointX = kWidth / 2;
const int kQuestionPointY = (kHeight * 2) / 7;
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

const int kConfidenceNotSet = -1;
const int kMaxConfidenceNotSet = -1;
const int kMinConfidenceNotSet = 1;

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
void ofApp::setup() {
    ofRegisterURLNotification(this);
    
    SetupArguments();
    SetupGui();
    
    if (using_socket_) {
        SetupMitm();
    }
}

/**
 * Process the command line arguments
 */
void ofApp::ProcessArguments() {
    cout << "Processing commandline arguments" << endl;
    
    if (is_test_) {
        // Load all the questions and answers to test with
        string source = args_[kTestFileArgIndex];
        ProcessTestFile(source);
        
        question_ = test_questions_[0];
        for (int i = 0; i < kAnswerCount; i++) {
            answers_[i] = test_answers_[0][i];
        }
        
        found_answer_ = false;
        answering_ = false;
        ResetConfidences();
    } else if (is_slave_) {
        // Prepare to receive answer from master
        bridge_.Init();
        found_answer_ = true;
        answering_ = false;
    } else {
        // Load single question and answers
        question_ = Trim(args_[kQuestionArgIndex]);
        
        for (int i = 0; i < kAnswerCount; i++) {
            answers_[i] = Trim(args_[i + 1]);
        }
        
        is_manual_ = true;
        found_answer_ = false;
        answering_ = false;
        ResetConfidences();
    }
    
    using_socket_ = false;
}

/**
 * Process the questions and answers from the given file
 */
void ofApp::ProcessTestFile(string source) {
    ofxJSONElement json;
    json.open(source);
    
    cout << "Parsed test JSON:" << endl;
    
    std::size_t size = json["questions"].size();
    for (Json::ArrayIndex i = 0; i < size; i++) {
        string question = json["questions"][i]["question"].asString();
        cout << "Adding question for testing: " << question << endl;
        
        vector<string> answers;
        answers.push_back(json["questions"][i]["answer1"].asString());
        answers.push_back(json["questions"][i]["answer2"].asString());
        answers.push_back(json["questions"][i]["answer3"].asString());
        answers.push_back(json["questions"][i]["answerc"].asString());
        
        test_questions_.push_back(question);
        test_answers_.push_back(answers);
    }
}

/**
 * Setup and process the command line arguments if there are any
 */
void ofApp::SetupArguments() {
    cout << "Apply command line arguments [" << args_.size() << "]" << endl;
    // Print out the arguments
    for (string arg : args_) {
        cout << " :" << arg << endl;
    }
    
    if (args_.size() >= kMinArgCount) {
        // Manually running a question
        cout << "Applying arguments for running" << endl;
        ProcessArguments();
    } else if (args_.size() == kTestArgCount) {
        // Automated testing with question bank or an error
        if (args_[kTestArgIndex] == "test") {
            cout << "Applying arguments for testing" << endl;
            is_test_ = true;
            ProcessArguments();
        } else {
            cout << "Wrong number of arguments" << endl;
        }
    } else if (args_.size() == kSlaveArgCount) {
        // Slave to external program
        if (args_[kSlaveArgIndex] == "slave") {
            cout << "Running in slave mode" << endl;
            is_slave_ = true;
            ProcessArguments();
        }
    } else {
        cout << "Not processing arguments" << endl;
    }
    
    question_ = BreakIntoLines(question_, kQuestionLineWidth);
}

/**
 * Setup and load the gui resources like fonts and images
 */
void ofApp::SetupGui() {
    ofSetBackgroundColor(kBgColor);
    
    iphone_x_.load("images/iphone_x.png");
    iphone_x_connected_.load("images/iphone_x_cxn.png");
    
    cabin_.load("fonts/Cabin-Regular.ttf", kRegularSize);
    cabin_bold_.load("fonts/Cabin-Bold.ttf", kBoldSize);
}

/**
 * Setup the connection with HQ server using the MITM strategy
 */
void ofApp::SetupMitm() {
    cout << "Setting up MITM" << endl;
    
    mitm_.SetupConstantHeaders();
    mitm_.SetupBroadcast(kBroadcastUrl);
    mitm_.EmulatePhoneConnection();
    
    if (mitm_.GameIsActive()) {
        cout << "Game is active, preparing socket" << endl;
        mitm_.ExtractSocketUrl();
        mitm_.SetupSocket();
        
        SetupSwift();
    } else {
        cout << "Game is not active, try again later" << endl;
    }
}

/**
 * Setup the Swift socket connection code using values retrieved from MITM
 */
void ofApp::SetupSwift() {
    cout << "Setting up Swift bridge" << endl;
    
    SocketHandler.url = @(mitm_.GetSocketUrl().c_str());
    
    SocketHandler.custom_header_keys = ConvertStringVector(GetMapKeys(mitm_.GetSocketHeaders()));
    SocketHandler.custom_header_values = ConvertStringVector(GetMapValues(mitm_.GetSocketHeaders()));
    
    [SocketHandler connect];
}

/* UPDATE */

//--------------------------------------------------------------
void ofApp::update() {
    if (using_socket_) {
        UpdateSocket();
    }
    
    if (!found_answer_ && !answering_) {
        AnswerQuestion();
    } else {
        CheckForAnswer();
    }
}

/**
 * Update the web socket connection and check for new questions
 */
void ofApp::UpdateSocket() {
    bool connected = SocketHandler.connected;
    mitm_.SetConnected(connected);
    
    if (connected) {
        string latest_message = GetLatestMessage();
        
        if (!latest_message.empty()) {
            if (latest_message != mitm_.GetLatestMessage()) {
                // Received a new message since it is different than the previously stored one
                PrintColorful("Received new message: " + latest_message, YELLOW);
                
                mitm_.SetLatestMessage(latest_message);
                mitm_.UpdateFromMessage(question_, answers_);
                
                UpdateQuestion(question_, answers_);
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

/**
 * Update the current question and answers and prepare to look for results
 */
void ofApp::UpdateQuestion(string question, vector<string> answers) {
    cout << "Updating current question and answers" << endl;
    PrintColorful("Question: " + question, YELLOW);
    
    for (int i = 0; i < answers.size(); i++) {
        PrintColorful("Answer: " + answers[i], YELLOW);
    }
    
    found_answer_ = false;
    answering_ = false;
    
    if (!Contains(question, "\n")) {
        question_ = BreakIntoLines(question, kQuestionLineWidth);
        answers_ = answers;
    }
    
    ResetConfidences();
}

/**
 * Find the answer to the given question
 */
void ofApp::AnswerQuestion() {
    cout << "Answering current question" << endl;
    answering_ = true;
    should_negate_ = GetNegation(question_);
    
    sleuth_.Investigate(question_, answers_);
}

/**
 * Reset the confidence levels for the answers
 */
void ofApp::ResetConfidences() {
    cout << "Resetting confidence levels" << endl;
    
    for (int i = 0; i < kAnswerCount; i++) {
        confidences_[i] = kConfidenceNotSet;
    }
    
    max_confidence_ = kMaxConfidenceNotSet;
    min_confidence_ = kMinConfidenceNotSet;
}

/**
 * Check for the answers to be updated
 */
void ofApp::CheckForAnswer() {
    if(!found_answer_) {
        // Check to see if the answer has been chosen
        if (sleuth_.finished_basic_ && sleuth_.finished_wikipedia_basic_) {
            if (max_confidence_ < 0) {
                // Confidence levels have been finalized
                for (double confidence : confidences_) {
                    if (confidence > max_confidence_ && confidence >= 0) {
                        max_confidence_ = confidence;
                        found_answer_ = true;
                        answering_ = false;
                    }
                    
                    if (confidence < min_confidence_ && confidence >= 0) {
                        min_confidence_ = confidence;
                        found_answer_ = true;
                        answering_ = false;
                    }
                }
            }
        }
    } else {
        if (!done_testing_ && !is_manual_ && !using_socket_ && !is_slave_) {
            // Only runs during automated testing. Choose the answer and continue testing
            for (int i = 0; i < kAnswerCount; i++) {
                if (ApproxEquals(confidences_[i], max_confidence_) && !should_negate_) {
                    chosen_answer_ = answers_[i];
                } else if (ApproxEquals(confidences_[i], min_confidence_) && should_negate_) {
                    chosen_answer_ = answers_[i];
                }
                
                cout << "Confidence #" << (i + 1) << ": " << confidences_[i] << endl;
            }
            
            if (is_test_) {
                AdvanceTesting();
            }
        } else {
            if (is_slave_ && !answering_) {
                // Running in slave mode, need to get new input
                if (bridge_.CheckBridgeReady()) {
                    if (!bridge_.GetQuestion().empty()) {
                        UpdateQuestion(bridge_.GetQuestion(), bridge_.GetAnswers());
                    }
                }
            }
        }
    }
}

/**
 * Continue testing if applicable, accepting next question
 */
void ofApp::AdvanceTesting() {
    // Choose the correct answer
    PrintColorful("Chosen correct answer to be: " + chosen_answer_, YELLOW);
    PrintColorful("Actual correct answer is   : " + test_answers_[current_test_index_][kAnswerCount], YELLOW);
    
    correct_answers_.push_back(chosen_answer_ == test_answers_[current_test_index_][kAnswerCount]);
    chosen_answers_.push_back(chosen_answer_);
    test_confidences_.push_back(confidences_);
    
    current_test_index_++;
    if (current_test_index_ < test_questions_.size()) {
        // Load the next test question and answers
        question_ = BreakIntoLines(test_questions_[current_test_index_], kQuestionLineWidth);
        for (int i = 0; i < kAnswerCount; i++) {
            answers_[i] = test_answers_[current_test_index_][i];
        }
        
        UpdateQuestion(question_, answers_);
    } else {
        // Print the final results
        done_testing_ = true;
        PrintTestResults();
    }
}

/**
 * Print out the test results for the full question bank
 */
void ofApp::PrintTestResults() {
    cout << "Test has concluded" << endl;
    
    int correct_count = 0;
    for (int i = 0; i < correct_answers_.size(); i++) {
        if (!correct_answers_[i]) {
            // Only give data on incorrect choices
            cout << "Got question incorrect: " << endl;
            PrintColorful("Question: " + test_questions_[i], YELLOW);
            PrintColorful("Should have chosen: " + test_answers_[i][kAnswerCount], GREEN);
            PrintColorful("Instead it chose  : " + chosen_answers_[i], RED);
            
            cout << "Choices: " << endl;
            for (int answer_index = 0; answer_index < kAnswerCount; answer_index++) {
                // Print out the confidences that went into making the decision
                cout << " :" << test_answers_[i][answer_index] << endl;
                cout << " : confidence :" << test_confidences_[i][answer_index] << endl;
            }
        } else {
            correct_count++;
        }
    }
    
    string accuracy = std::to_string(correct_count) + " / " + std::to_string(correct_answers_.size());
    PrintColorful("Accuracy: " + accuracy, YELLOW);
}

/* DRAW */

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
    DrawTextPointCentered(question_, cabin_bold_, kQuestionPointX, kQuestionPointY);
}

/**
 * Modifies the color scheme for the following answer depending on confidence level
 */
void ofApp::UpdateAnswerColors(double confidence) {
    if (ApproxEquals(confidence, max_confidence_) && max_confidence_ >= 0 && !should_negate_) {
        current_shape_color_ = kCorrectColor;
        current_text_color_ = kWhiteColor;
    } else if (ApproxEquals(confidence, min_confidence_) && min_confidence_ >= 0 && should_negate_) {
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
        
        // Render the outlines of the answer boxes
        ofSetColor(kOutlineColor);
        ofSetLineWidth(kAnswerLineWidth);
        ofNoFill();
        
        ofDrawRectRounded(kAnswerBox.getX(),
                          kAnswerBox.getY() + y_offset,
                          kAnswerBox.getWidth(),
                          kAnswerBox.getHeight(),
                          kAnswerRectRounding);
        
        // Render the backgrounds of the answer boxes
        ofFill();
        
        UpdateAnswerColors(confidences_[i]);
        
        ofSetColor(current_shape_color_);
        
        if (confidences_[i] >= 0) {
            ofDrawRectRounded(kAnswerBox.getX(),
                              kAnswerBox.getY() + y_offset,
                              (int) (kAnswerBox.getWidth() * std::min(std::max(confidences_[i], min_render_confidence_), 1.0)),
                              kAnswerBox.getHeight(),
                              kAnswerRectRounding);
        }
        
        // Render the answer text
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
    
    if (mitm_.IsConnected()) {
        iphone_x_connected_.draw(0, 0, kWidth, kHeight);
    } else {
        iphone_x_.draw(0, 0, kWidth, kHeight);
    }
}

/**
 * Draw text centered with the given font and given offsets
 */
void ofApp::DrawTextScreenCentered(string text, ofTrueTypeFont &font, int x, int y) {
    ofRectangle box = font.getStringBoundingBox(text, x, y);
    font.drawString(text, x + (kWidth - box.getWidth()) / 2, y + (kHeight - box.getHeight()) / 2);
}

/**
 * Draw text centered at the given x and y position
 */
void ofApp::DrawTextPointCentered(string text, ofTrueTypeFont &font, int x, int y) {
    ofRectangle box = font.getStringBoundingBox(text, x, y);
    font.drawString(text, x - box.getWidth() / 2, y - box.getHeight() / 2);
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

/**
 * Receive a response event from a URL async request
 */
void ofApp::urlResponse(ofHttpResponse &response) {
    if (response.status == kHttpGood) {
        cout << "Good async response" << endl;
        //cout << response.data << endl;
        
        sleuth_.ReceiveResponse(response, question_, answers_, confidences_);
    } else {
        cout << "Bad async response:" << endl;
        cout << response.status << " " << response.error << endl;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    if (w != kWidth || h != kHeight) {
        // Prevent window resizing
        ofSetWindowShape(kWidth, kHeight);
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

/* GETTERS AND SETTERS */

void ofApp::SetArgs(vector<string> args) {
    args_ = args;
}

