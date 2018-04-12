#include "ofMain.h"
#include "ofApp.h"

/**
 Final Project: Holmes
    by Jeff Taylor-Chang 2018
 
 EXPLANATION:
    The core of Holmes is built in C++ using OpenFrameworks and various ofx libraries that handle
 web protocols. However, in order to properly incorporate an added feature of WebSockets, I found
 the ofx Web Socket library to be too weak for my purposes since it wouldn't allow me to fully customize
 headers. My solution was to create bridging files (all .mm files) which can run both Objective-C and
 C++ code, allowing me to write primarily in C++ but then call to Swift code in Objective-C. I was then
 able to write the Web Socket code in Swift using a Swift library (WebSocket.swift). My bridge files
 access the variables in the Swift class and call its member functions, and can properly receive the
 results allowing me to utilize the additional libraries I needed.
 
 BUILDING:
    Holmes must be built as a Release target because it needs to compile a linker library between
 the Objective-C++ files and the Swift bridge which connects to the Swift WebSocket library. It will
 not compile properly if done in Debug mode.
 
 LIBRARIES AND CREDIT:
    - ofxGUI
    - ofxJSON
    - ofxHTTP
    - ofxIO
    - ofxMediaType
    - ofxNetworkUtils
    - ofxSSLManager
    - ofxTaskQueue
    - WebSocket
 */

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
