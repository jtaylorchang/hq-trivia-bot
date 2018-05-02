#include "ofMain.h"
#include "ofApp.h"
#include "tests.hpp"

using std::string;
using std::vector;

const int kWindowWidth = 354;
const int kWindowHeight = 768;

/**
 * Create a vector from command line arguments
 *
 * @param argc the argument count
 * @param argv the argument array
 */
vector<string> ProcessArgs(int argc, char *argv[]) {
    vector<string> args;
    
    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }
    
    return args;
}

/**
 * Check if the program should be run in test mode or not
 */
bool RunningTestMode(vector<string> args) {
    return (!args.empty() && (args[0] == "testmode"));
}

//========================================================================
int main(int argc, char *argv[]) {
    vector<string> processed_args = ProcessArgs(argc, argv);
    if (RunningTestMode(processed_args)) {
        // Run tests. Do not instantiate OpenFrameworks
        RunTestMode();
    } else {
        // Run OpenFrameworks application
        ofSetupOpenGL(kWindowWidth, kWindowHeight, OF_WINDOW);
        
        ofApp *holmes = new ofApp();
        holmes->SetArgs(processed_args);
        
        ofRunApp(holmes);
    }
}
