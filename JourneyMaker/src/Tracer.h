//
//  Tracer.h
//
//  Created by Patricio Gonzalez Vivo on 9/12/13.
//
//

#pragma once

#include "UIProject.h"
#include "UIMapBackground.h"

#include "UIMap.h"
#include "StreetView.h"

struct Step{
    
    Step(StreetView &_sv){
        *this = _sv;
    }
    
    Step& operator=(StreetView &_sv){
        loc = _sv.getLocation();
        pano_id = _sv.getPanoId();
        links = _sv.links;
        direction = _sv.getDirection();
    }
    
    Location loc;
    string  pano_id;
    vector<Link> links;
    
    int     nDirection;
    
    double  angle;
    float   direction;
};

class Tracer : public UI2DProject {
public:
    
    string getSystemName(){return "Tracer";}
    
    void selfSetupGuis();
    
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);
    
    void selfSetup();
    void selfUpdate();
    void selfDraw();
    void selfEnd();

    void selfWindowResized(ofResizeEventArgs & args);
    
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void selfMouseDragged(ofMouseEventArgs& data);
    void selfMouseMoved(ofMouseEventArgs& data);
    void selfMousePressed(ofMouseEventArgs& data);
    void selfMouseReleased(ofMouseEventArgs& data);

    void urlResponse(ofHttpResponse & response);
    
protected:
    int  getCloser(const vector<Link> &_links, float _angle);
    void changePathAt(int _nIndex, int _link);
    void addView(Step _view);
    
    UIMap               map;
    
    MapExtent           mapExtent;
    Location            mouseLocation;
    
    ofxUITextInput      *origin;
    ofxUITextInput      *destiny;
    
    vector<Location>    directions;
    ofPolyline          directionsLine;
    bool                directionsLoaded;
    
    Location            nextToLoad;
    int                 nLoading;
    
    vector<Step>        path;
    ofPolyline          pathLine;
    StreetView          pathHeader;
    
    int                 nSelected;
    bool                bDirAngle;
    bool                bSave, bClear;
};
