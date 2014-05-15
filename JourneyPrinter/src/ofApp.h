#pragma once

#include "ofMain.h"

#include "ofxPiTFT.h"
#include "ofxThermalPrinter.h"

struct StepLoc {
    string  google_id;
    string  slice;
    float   lat,lon;
    string  address;
    string  region;
    string  country;
    
    string  map;
    ofPoint pos;
};

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
		
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    vector<StepLoc> steps;
    
    ofImage         img,map;
    ofPoint         pos;
    
    ofxThermalPrinter   printer;
    ofxPiTFT            tft;
    
    float   lastTime;
    int     nLoad;
};
