#pragma once

#include "ofMain.h"
#include "search_cred.hpp"
#include "sleuth.hpp"
#include "mitm.hpp"
#include "categorizer.hpp"
#import "Holmes-Swift.h"

using std::string;
using std::cout;
using std::endl;

class ofApp : public ofBaseApp {
    
private:
    vector<string> args_;
    
    /* TEST VARIABLES */
    
    int current_test_index_ = 0;             // The current index in automated tests
    vector<string> test_questions_;             // The questions for the automated tests
    vector<vector<string>> test_answers_;       // The answers for the automated tests
    vector<bool> correct_answers_;              // If it was correct for each test
    vector<string> chosen_answers_;             // Answer chosen for each automated test
    vector<vector<double>> test_confidences_;   // Confidences for each automated test
    string chosen_answer_ = "";                 // Answer chosen during testing
    bool done_testing_ = false;                 // Automated testing is complete
    bool is_manual_ = false;                    // Run from commandline, single Q
    
    /* LOGIC INSTANCE VARIABLES */
    
    Sleuth sleuth_;
    Mitm mitm_;
    
    /* GRAPHICS VARIABLES */
    
    ofImage iphone_x_;
    ofImage iphone_x_connected_;
    ofTrueTypeFont cabin_;
    ofTrueTypeFont cabin_bold_;
    ofColor current_shape_color_;
    ofColor current_text_color_;
    
    /* DEFAULT VALUES BEFORE GAME STARTS */
    
    string question_ = "How long does the average game of HQ Trivia take to start?";
    vector<string> answers_ = {
        "Two hours",
        "Ten years",
        "An eternity"
    };
    
    // Arbitrarily chosen confidence levels just to show default working
    vector<double> confidences_ = {
        0.10,
        0.40,
        0.90
    };
    
    bool answering_ = false;
    bool found_answer_ = true;
    
    // Minimum confidence that the confidence bar will render accurately
    double min_render_confidence_ = 0.20;
    
    // Current min confidence (should equal the smallest value in the vector)
    double min_confidence_ = 0.10;
    
    // Current max confidence (should equal the largest value in the vector)
    double max_confidence_ = 0.90;
    
    // Whether to use the max (false) or min (true) confidence
    bool should_negate_ = false;
    
    // Using a socket connection vs command line
    bool using_socket_ = true;
    
    // Using automated test data
    bool is_test_ = false;

public:
    /* SETUP */
    void setup();
    
    /**
     * Process the command line arguments
     */
    void ProcessArguments();
    
    /**
     * Process the questions and answers from the given file
     *
     * @param source the file to load
     */
    void ProcessTestFile(string source);
    
    /**
     * Print and process the command line arguments if there are any
     */
    void SetupArguments();
    
    /**
     * Setup and load the gui resources like fonts and images
     */
    void SetupGui();
    
    /**
     * Setup the connection with HQ server using the MITM strategy
     */
    void SetupMitm();
    
    /**
     * Setup the Swift socket connection code using values retrieved from MITM
     */
    void SetupSwift();
    
    /* UPDATE */
    void update();
    
    /**
     * Update the web socket connection and check for new questions
     */
    void UpdateSocket();
    
    /**
     * Get the latest message from the Swift socket
     *
     * @return the latest message converted from NSString to std::string
     */
    string GetLatestMessage();
    
    /**
     * Find the answer to the given question
     */
    void AnswerQuestion();
    
    /**
     * Reset the confidence levels for the answers
     */
    void ResetConfidences();
    
    /**
     * Check for the answers to be updated
     */
    void CheckForAnswer();
    
    /**
     * Continue testing if applicable, accepting next question
     */
    void AdvanceTesting();
    
    /**
     * Print out the test results for the full question bank
     */
    void PrintTestResults();
    
    /* DRAW */
    void draw();
    
    /**
     * Draw the question and question background
     */
    void DrawQuestion();
    
    /**
     * Modifies the color scheme for the following answer depending on confidence level
     *
     * @param confidence the confidence in the answer
     */
    void UpdateAnswerColors(double confidence);
    
    /**
     * Draw the answer options and confidence levels
     */
    void DrawAnswers();
    
    /**
     * Draw the overlay with the status bar and frame
     */
    void DrawStatusBar();
    
    /**
     * Draw text centered with the given font and given offsets
     *
     * @param text the text to draw
     * @param font the font to use
     * @param x the x offset
     * @param y the y offset
     */
    void DrawTextScreenCentered(string text, ofTrueTypeFont &font, int x, int y);
    
    /**
     * Draw text centered at the given x and y position
     *
     * @param text the text to draw
     * @param font the font to use
     * @param x the x offset
     * @param y the y value to center around
     */
    void DrawTextPointCentered(string text, ofTrueTypeFont &font, int x, int y);
    
    /**
     * Draw text vertically centered at the given x and y position
     *
     * @param text the text to draw
     * @param font the font to use
     * @param x the x offset
     * @param y the y value to center around
     */
    void DrawTextVerticalCenter(string text, ofTrueTypeFont &font, int x, int y);
    
    /* OBJ-C++ UTILITIES */
    
    /**
     * Converts a vector of strings from C++ to an array of NSStrings in Objective-C
     *
     * @param string_vector the vector of strings to convert
     * @return the array of NSStrings
     */
    id ConvertStringVector(vector<string> string_vector);
    
    /* EVENTS */
    
    /**
     * Receive a response event from a URL async request
     *
     * @param response the response from the request
     */
    void urlResponse(ofHttpResponse &response);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    /* GETTERS AND SETTERS */
    
    void SetArgs(vector<string> args);
		
};
