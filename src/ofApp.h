#pragma once

#include "ofMain.h"
#include "search_cred.hpp"
#include "sleuth.hpp"
#include "mitm.hpp"
#import "Holmes-Swift.h"

using std::string;

class ofApp : public ofBaseApp{
    
private:
    ofImage iphone_x_;
    ofImage iphone_x_connected_;
    ofTrueTypeFont cabin_;
    ofTrueTypeFont cabin_bold_;
    Mitm mitm_;
    ofColor current_shape_color_;
    ofColor current_text_color_;
    
    string question_ = "How long does the\naverage game of HQ\nTrivia take to start?";
    string answer1_ = "Two hours";
    string answer2_ = "Ten years";
    string answer3_ = "An eternity";
    
    /* DEFAULT VALUES */
    
    double confidence1_ = 0.10;
    double confidence2_ = 0.40;
    double confidence3_ = 0.90;
    double min_confidence_ = 0.20;
    double max_confidence_ = 0.90;

public:
    /* SETUP */
    void setup();
    
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
     * Get the latest message from the Swift socket
     *
     * @return the latest message converted from NSString to std::string
     */
    string GetLatestMessage();
    
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
    void DrawTextCentered(string text, ofTrueTypeFont &font, int x, int y);
    
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
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
};
