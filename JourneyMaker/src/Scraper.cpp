//
//  Scraper.cpp
//
//  Created by Patricio Gonzalez Vivo on 9/12/13.
//
//

#include "Scraper.h"

void Scraper::selfSetup(){
    ofSetVerticalSync(true);
    ofSetFullscreen(false);
    
    ofBuffer tripBuffer = ofBufferFromFile("BEACON.txt");
    for (int i = 0; i < tripBuffer.size(); i++) {
        ids.push_back(tripBuffer.getNextLine());
    }
    
    nLoad = 0;
    sv.setZoom(1);
    sv.setPanoId(ids[nLoad]);
    
    map.allocate(320, 240);
    map.loadMap("Stamen-toner");
    map.setZoom(15);
    
    nCounter = 0;
    nMapCounter = 0;
}

void Scraper::selfSetupGuis(){
    guiAdd(map);
}

void Scraper::selfSetupSystemGui(){
    sysGui->addSlider("Angle", 0, 360, &view_ang);
    sysGui->addSlider("Amplitud", 0, 1.0, &view_amp);
}

void Scraper::guiSystemEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();

}

void Scraper::selfSetupRenderGui(){

}

void Scraper::guiRenderEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
}

void Scraper::selfUpdate(){
    map.update();
    
    sv.update();
    
    if(sv.isTextureLoaded()){
        if(nLoad == 0){
            map.setCenter(sv.getLocation());
            map.setZoom(15);
        } else {
            float dir = prevLoc.getDegTo(sv.getLocation());
            float dist = prevLoc.getDistanceTo(sv.getLocation());
            
            ofTexture slice = sv.getTextureAt(dir+view_ang, dist*view_amp);
            views.push_back(slice);
            
            ofPixels sPixels;
            slice.readToPixels(sPixels);
            
            float w = (slice.getWidth()/(slice.getHeight()))*384.0*1.4;
            float h = 384.0;
            
            ofFbo miniSlice;
            miniSlice.allocate(w,h);
            miniSlice.begin();
            ofClear(0);
            slice.draw(0,0,miniSlice.getWidth(),miniSlice.getHeight()*1.4);
            miniSlice.end();
            
            ofPixels pixels;
            pixels.allocate(miniSlice.getWidth(), miniSlice.getHeight(), 3);
            miniSlice.readToPixels(pixels);
            pixels.rotate90(1);
            
            pos = map.locationPoint(sv.getLocation());
            
            ofRectangle mapArea = ofRectangle(0,0,map.getWidth(),map.getHeight());
            if(!mapArea.inside(pos)){
                ofPixels mapPixels;
                mapPixels.allocate(320, 240,3);
                map.getTextureReference().readToPixels(mapPixels);
                ofSaveImage(mapPixels, getDataPath()+"maps/"+ofToString(nMapCounter,5,'0')+".png");
                nMapCounter++;
                
//                if (pos.y <= 0 ) {
//                    map.setCenter(map.getCenterCoordinate().up());
//                } else if ( pos.y >= mapArea.height ) {
//                    map.setCenter(map.getCenterCoordinate().down());
//                } else if ( pos.x <= 0 ) {
//                    map.setCenter(map.getCenterCoordinate().left());
//                } else if ( pos.x >= mapArea.width ) {
//                    map.setCenter(map.getCenterCoordinate().right());
//                }
                
                map.setCenter(sv.getLocation());
                pos = map.locationPoint(sv.getLocation());
            }
            
            StepLoc s;
            s.google_id = ids[nLoad];
            s.slice = "slices/"+ofToString(nCounter,5,'0')+".png";
            s.lat = sv.getLocation().lat;
            s.lon = sv.getLocation().lon;
            s.address = sv.getAddress();
            s.region = sv.getRegion();
            s.country = sv.getCountry();
            
            s.map = "maps/"+ofToString(nMapCounter,5,'0')+".png";
            s.pos = pos;
            
            steps.push_back(s);
            
            ofSaveImage(pixels, getDataPath()+s.slice);
            nCounter++;
            
            ofBuffer buf;
            for(int i = 0; i < steps.size(); i++){
                buf.append(steps[i].google_id + "," +
                           steps[i].slice + "," +
                           ofToString(steps[i].lat) + "," +
                           ofToString(steps[i].lon) + "," +
                           steps[i].address + "," +
                           steps[i].region + "," +
                           steps[i].country + "," +
                           steps[i].map + "," +
                           ofToString(steps[i].pos.x) + "," +
                           ofToString(steps[i].pos.y) + "\n");
            }
            ofBufferToFile(getDataPath()+"steps.csv", buf);
            
        }
        prevLoc = sv.getLocation();
        nLoad++;
        sv.setPanoId(ids[nLoad]);
        
    }
}

void Scraper::selfDraw(){
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofGetWidth(), 0);
    ofSetColor(255,200);
    
    int x = 0;
    for(int i = views.size()-1; i >=0 ; i--){
        x += views[i].getWidth();
        views[i].draw(-x,0);
    }
    
    if(x>ofGetScreenWidth()){
        views.erase(views.begin()+0);
    }
    
    ofTranslate(-320,sv.getHeight());
    map.draw();
    ofSetColor(255, 0, 0);
    ofCircle(pos, 3);
    
    ofPopStyle();
    ofPopMatrix();
    
}

void Scraper::selfKeyPressed(ofKeyEventArgs & args){
}

void Scraper::selfKeyReleased(ofKeyEventArgs & args){
}

void Scraper::selfMouseMoved(ofMouseEventArgs& data){
}

void Scraper::selfMousePressed(ofMouseEventArgs& data){
}

void Scraper::selfMouseDragged(ofMouseEventArgs& data){
}

void Scraper::selfMouseReleased(ofMouseEventArgs& data){
}

void Scraper::selfWindowResized(ofResizeEventArgs & args){
    
}