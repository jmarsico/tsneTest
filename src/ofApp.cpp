#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    runManually = true;
    ofEnableDepthTest();
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableIndices();
    
    int numDataPoints = 1000;
    ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE);
    csvLoader.load("testData.csv");
    
    double x;
    x = ofToInt(csvLoader[1][0]);
    //ofLog() << (x + 1);
    
//    vector<ofColor> groupColors = vector<ofColor>{ofColor::green, ofColor::yellow, ofColor::orange ,ofColor::red};
    
    
    ofEnableLighting();
    light.setPosition(ofGetWidth()/2, ofGetHeight()/2, 500);
    light.setAmbientColor(ofFloatColor(0.8));
    light.setDiffuseColor(ofFloatColor(0.9));
    light.setDirectional();
    
    sleepDataPoint tempPoint;
    for (int i = 1; i < (numDataPoints + 1); i++) {
        tempPoint.numChildren = ofToInt(csvLoader[i][7]);
        tempPoint.bath = ofToInt(csvLoader[i][27]);
        tempPoint.watchTV = ofToInt(csvLoader[i][31]);
        tempPoint.drinkAlcohol = ofToInt(csvLoader[i][28]);
        tempPoint.read = ofToInt(csvLoader[i][29]);
        tempPoint.sleepQuality = ofToInt(csvLoader[i][17]);
        tempPoint.color = 60 * tempPoint.sleepQuality;
        dataPoints.push_back(tempPoint);
        
        mesh.addVertex(ofVec3f(0,0,0));
        
    }
    //ofLog() << dataPoints[0].bath;
    
    vector<vector<float>> data;
    vector<float> tempData;
    
    for (int i = 0 ; i < numDataPoints; i++) {
        tempData.push_back(dataPoints[i].numChildren);
        tempData.push_back(dataPoints[i].bath);
        tempData.push_back(dataPoints[i].watchTV);
        tempData.push_back(dataPoints[i].drinkAlcohol);
        tempData.push_back(dataPoints[i].read);
        tempData.push_back(dataPoints[i].sleepQuality);
        
        data.push_back(tempData);
        tempData.clear();
    }
    
    int dims = 3;
    float perplexity = 40;
    float theta = 0.2;
    bool normalize = true;
    
    tsnePoints = tsne.run(data ,dims,perplexity,theta,normalize, runManually);
    //ofLog() << data[0][1];
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if (runManually) {
        tsnePoints = tsne.iterate();
        for (int i=0; i<dataPoints.size(); i++) {
            dataPoints[i].tsnePoint = ofPoint(ofGetWidth() * tsnePoints[i][0], ofGetHeight() * tsnePoints[i][1], 1000 * tsnePoints[i][2]);
            dataPoints[i].tsneTransparency = tsnePoints[i][2];
            mesh.setVertex(i, dataPoints[i].tsnePoint);
        }
        
        //set up indices
        mesh.clearIndices();
        for(int a = 0; a < dataPoints.size(); a++){
            ofVec3f verta = mesh.getVertex(a);
            for(int b = a + 1; b < dataPoints.size(); b++){
                ofVec3f vertb = mesh.getVertex(b);
                float distance = verta.distance(vertb);
                if (distance <= 60) {
                    // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
                    // connected to form a line
                    mesh.addIndex(a);
                    mesh.addIndex(b);
                }
            }
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    cam.begin();
    light.enable();
    
    ofSetLineWidth(2);
    mesh.draw();
    for (int i=0; i<dataPoints.size(); i++) {
        float x = dataPoints[i].tsnePoint.x;
        float y = dataPoints[i].tsnePoint.y;
        float z = dataPoints[i].tsnePoint.z;
        ofSetColor(dataPoints[i].color);
        ofDrawSphere(x, y, z, 10);
        
    }
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
