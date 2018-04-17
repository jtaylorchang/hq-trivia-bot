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
    void SetupGui();
    void SetupMitm();
    void SetupSwift();
    string GetLatestMessage();

    void setup();
    void update();
    void draw();
    
    void DrawQuestion();
    void UpdateAnswerColors(double confidence);
    void DrawAnswers();
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
    void DrawTextVerticalCenter(string text, ofTrueTypeFont &font, int x, int y);

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
    
    /* OBJ-C++ UTILITIES */
    
    /**
     * Converts a vector of strings from C++ to an array of NSStrings in Objective-C
     *
     * @param string_vector the vector of strings to convert
     * @return the array of NSStrings
     */
    id ConvertStringVector(vector<string> string_vector);
		
};
