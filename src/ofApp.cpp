#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    
    syphon.setName("tsne");
    
    gui.setup();
    gui.add(distanceThresh.set("dist thresh", 200.0, 10.0, 500.0));
    gui.add(rad.set("radius", 10, 1.0, 60.0));
    gui.add(meshCol.set("mesh color", 0.0, 0.0, 1.0));
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableIndices();
//    mesh.enableColors();
    
    int numDataPoints = 1000;
    ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE);
    csvLoader.load("testData.csv");
    
    double x;
    x = ofToInt(csvLoader[1][0]);
    

    ofEnableLighting();
    light.setPosition(ofGetWidth()/2, ofGetHeight()/2, 500);
    light.setAmbientColor(ofFloatColor(0.8));
    light.setDiffuseColor(ofFloatColor(0.9));
    light.setDirectional();
    
    
    for (int i = 1; i < (numDataPoints + 1); i++) {
        SleepDataPoint tempPoint;
        tempPoint.init();
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
    
    tsnePoints = tsne.run(data ,dims,perplexity,theta,normalize, true);
    //ofLog() << data[0][1];
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    int bReadyforNext = 0;
    
    for(int i = 0; i < dataPoints.size(); i++){
        
        dataPoints[i].update();
        mesh.getVertices()[i] = dataPoints[i].currentPoint;
        
        if(dataPoints[i].bReadyForNextPoint == true){
            bReadyforNext++;
        }
    }
    
    if(bReadyforNext == dataPoints.size()){
//    if(true){
        ofLog() << "iterate";
        tsnePoints = tsne.iterate();
        for (int i=0; i<dataPoints.size(); i++) {
            dataPoints[i].addNewPoint(ofPoint(ofGetWidth() * tsnePoints[i][0], ofGetHeight() * tsnePoints[i][1], 1000 * tsnePoints[i][2]));
            dataPoints[i].tsneTransparency = tsnePoints[i][2];
        }
    }
    
    

    
    
    //set up indices
    mesh.clearIndices();
    mesh.clearColors();
    
    //update the dataPoint, lerp
    for(int a = 0; a < dataPoints.size(); a++){
    
        ofVec3f verta = mesh.getVertex(a);
        for(int b = a + 1; b < dataPoints.size(); b++){
            ofVec3f vertb = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= distanceThresh) {
                // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
                // connected to form a line
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
        }
    }
        
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(80), ofColor(30));
    ofEnableLighting();
    ofEnableDepthTest();
    
    cam.begin();
    
    light.enable();
    ofSetColor(ofFloatColor(meshCol));
    mesh.draw();
    
    
    
    ofSetLineWidth(1);
    
    
    
    for (int i=0; i<dataPoints.size(); i++) {
        float x = dataPoints[i].currentPoint.x;
        float y = dataPoints[i].currentPoint.y;
        float z = dataPoints[i].currentPoint.z;
        ofSetColor(200);
        ofDrawSphere(x, y, z, rad);
        
    }
    
    cam.end();
    
    syphon.publishScreen();
    
    ofDisableLighting();
    ofDisableDepthTest();
    gui.draw();
}


void ofApp::reset(){
    vector<vector<float>> data;
    vector<float> tempData;
    
    for (int i = 0 ; i < dataPoints.size(); i++) {
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == ' '){
        reset();
    }

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
