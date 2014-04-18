#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    nLoad = 0;
    
#ifdef TARGET_RASPBERRY_PI
    printer.open("/dev/ttyAMA0");
#else
    printer.open("/dev/tty.PL2303-00002014");
#endif
    
    printer.setControlParameter(20, 80, 250);
    lastTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    float now = ofGetElapsedTimef();
    float diffTime = now-lastTime;
    
    if(nLoad < 6934 && diffTime>3.0){
        ofImage img;
        img.loadImage("slices/"+ofToString(nLoad,5,'0')+".png");
        img.update();
        printer.print(img);
        img.setAnchorPercent(0.5, 0.5);
        views.push_back(img);
        
        lastTime = now;
        ofLog(OF_LOG_VERBOSE,ofToString(nLoad)+" at "+ofToString(ofGetElapsedTimef()));
        nLoad++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    float scale = ofGetHeight()/384.0;
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofGetWidth(), 0);
    ofScale(scale, scale);
    ofSetColor(255,200);
    int xOffset = 0;
    for(int i = views.size()-1; i >=0 ; i--){
        xOffset += views[i].getHeight();
        ofPushMatrix();
        ofTranslate(-xOffset,views[i].getWidth());
        ofRotate(-90);
        views[i].draw(0,0);
        ofPopMatrix();
    }
    if(xOffset>ofGetScreenWidth()){
        views.erase(views.begin()+0);
    }
    
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}