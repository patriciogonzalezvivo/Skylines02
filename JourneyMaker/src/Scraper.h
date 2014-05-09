//
//  Scraper.h
//
//  Created by Patricio Gonzalez Vivo on 9/12/13.
//
//

#pragma once

#include "UIProject.h"
#include "UIMapBackground.h"

#include "UIMap.h"
#include "StreetView.h"

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

class Scraper : public UI2DProject {
public:
    
    string getSystemName(){return "Scraper";}
    
    void selfSetupGuis();
    
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);
    
    void selfSetup();
    void selfUpdate();
    void selfDraw();

    void selfWindowResized(ofResizeEventArgs & args);
    
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void selfMouseDragged(ofMouseEventArgs& data);
    void selfMouseMoved(ofMouseEventArgs& data);
    void selfMousePressed(ofMouseEventArgs& data);
    void selfMouseReleased(ofMouseEventArgs& data);

protected:
    StreetView  sv;
    ofTexture   tex;
    
    UIMap       map;
    ofPoint     pos;
    int         nMapCounter;
    
    vector<string> ids;
    vector<StepLoc> steps;
    vector<ofTexture> views;
    
    float       view_ang;
    float       view_amp;
    
    Location    prevLoc;
    int         nLoad;
    int         nCounter;
};
