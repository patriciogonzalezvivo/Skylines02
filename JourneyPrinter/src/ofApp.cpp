#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFullscreen(true);
    
    ofSetCircleResolution(36);
    
    nLoad = 0;
    
#ifdef TARGET_RASPBERRY_PI
    printer.open("/dev/ttyAMA0");
#else
    printer.open("/dev/tty.PL2303-00002014");
#endif
    
    ofBuffer buffer = ofBufferFromFile("steps.csv");
    while (!buffer.isLastLine()) {
		string line = buffer.getNextLine();
		
		//Split line into strings
		vector<string> words = ofSplitString(line, ",");
		
        if(words.size()>1){
            StepLoc s;
            s.google_id = words[0];
            s.slice = words[1];
            s.lat = ofToFloat(words[2]);
            s.lon = ofToFloat(words[3]);
            s.address = words[4];
            s.region = words[5];
            s.country = words[6];
            s.map = words[7];
            s.pos.x = ofToFloat(words[8]);
            s.pos.y = ofToFloat(words[9]);
            
            steps.push_back(s);
        }
	}
    
    printer.setControlParameter(20, 80, 250);
    lastTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    float now = ofGetElapsedTimef();
    float diffTime = now-lastTime;
    
    if(nLoad < 6934 && diffTime>3.0){
        
        ofImage img;
        img.loadImage(steps[nLoad].slice);
        img.update();
        printer.print(img);
        img.setAnchorPercent(0.5, 0.5);
        views.push_back(img);
        
        map.loadImage(steps[nLoad].map);
        
        pos = steps[nLoad].pos/ofPoint(320,240);
        pos *= ofPoint(ofGetWidth(),ofGetHeight());
        
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
    
    ofPushStyle();
    float alpha = ofMap(mouseX, 0, ofGetWidth(), 255, 0);
    ofSetColor(255, alpha);
    map.draw(0, 0, ofGetWidth(),ofGetHeight());
    ofSetColor(255, 0, 0, alpha);
    ofCircle(pos, 20);
    ofPopStyle();
    
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