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
    
    string question_ = "How long does it\ntake for HQ to start?";
    string answer1_ = "Two hours";
    string answer2_ = "Ten years";
    string answer3_ = "An eternity";

public:
    void SetupGui();
    void SetupMitm();
    void SetupSwift();
    string GetLatestMessage();

    void setup();
    void update();
    void draw();
    
    /**
     * Draw text centered with the given font and given offsets
     *
     * @param text the text to draw
     * @param font the font to use
     * @param x the x offset
     * @param y the y offset
     */
    void DrawTextCentered(string text, ofTrueTypeFont &font, int x, int y);

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
