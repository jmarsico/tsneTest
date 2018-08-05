#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    
    syphon.setName("tsne");
    
    twister.setup();
    depthOfField.setup(ofGetWidth(), ofGetHeight());
    
    gui.setup();
    gui.add(distanceThresh.set("dist thresh", 200.0, 10.0, 500.0));
    gui.add(rad.set("radius", 10, 1.0, 60.0));
   
    gui.add(transitionMillis.set("transition", 500, 100, 4000));
    gui.add(camDistance.set("cam dist", 500, 0, 7000));
    gui.add(camRotSpeedLat.set("cam rot speed x", 1.1, 0.01, 2.0));
    gui.add(camRotSpeedLon.set("cam rot speed y", 1.1, 0.01, 2.0));
    gui.add(ambAmb.set("amb amb", 0.5, 0.0, 1.0));
    gui.add(ambDiff.set("amb diff",0.5, 0.0, 1.0));
    gui.add(pointAmb.set("point amb", 0.5, 0.0, 1.0));
    gui.add(pointDiff.set("point diff", 0.5, 0.0, 1.0));
    gui.add(fov.set("FOV", 16, 0, 20));
    gui.add(bgColor.set("bg col", ofColor(100,100,100), ofColor(0.,0.,0.),ofColor(255,255,255)));
    gui.add(col1.set("col1", ofColor(100,100,100), ofColor(0.,0.,0.),ofColor(255,255,255)));
    gui.add(col2.set("col2", ofColor(100,100,100), ofColor(0.,0.,0.),ofColor(255,255,255)));
    gui.add(col3.set("col3", ofColor(100,100,100), ofColor(0.,0.,0.),ofColor(255,255,255)));
    gui.add(meshCol.set("mesh color", ofColor(100,100,100), ofColor(0.,0.,0.),ofColor(255,255,255)));
    
            
//    gui.add(bAutoFocus.set("auto focus", false));
//    gui.add(focusDistance.set("focus distance", 300, 0, 1000));
//    gui.add(aperture.set("aperture", 1, 0, 2000));
//    gui.add(blurAmount.set("blurAmount", 1, 0.7, 4.0));
    
    gui.loadFromFile("settings.xml");
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableIndices();
//    mesh.enableColors();
    
    prevCol1 = col1;
    prevCol2 = col2;
    prevCol3 = col3;
    prevCol4 = col4;
    
    int numDataPoints = 1000;
    ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE);
    csvLoader.load("testData.csv");
    
    numDataPoints = csvLoader.getNumRows() - 1;
    
    double x;
    x = ofToInt(csvLoader[1][0]);
    

    ofEnableLighting();
    light.setPosition(ofGetWidth()/2-200, ofGetHeight()/2-200, 500);
    light.setAmbientColor(ofFloatColor(0.2));
    light.setDiffuseColor(ofFloatColor(0.2));
    light.setDirectional();
    
    light2.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    light2.setAmbientColor(ofFloatColor(0.5));
    light2.setDiffuseColor(ofFloatColor(0.7));
    light2.setPointLight();
    
    
    
    
    
    
    
    for (int i = 1; i < (csvLoader.getNumRows()); i++) {
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
    
    
    ofLog() << "num points: " << dataPoints.size() << " | num mesh: " << mesh.getNumVertices();
    
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
    float perplexity = 50;
    float theta = 0.1;
    bool normalize = true;
    int maxIterations = 1000;
    int currentIteration = 0;
    
    tsnePoints = tsne.run(data ,dims,perplexity,theta,normalize, true);
    
    while(currentIteration < maxIterations){
        tsnePoints = tsne.iterate();
        for (int i=0; i<dataPoints.size(); i++) {
            dataPoints[i].addNewPoint(ofPoint(ofGetWidth() * tsnePoints[i][0], ofGetHeight() * tsnePoints[i][1], 1000 * tsnePoints[i][2]));
            dataPoints[i].tsneTransparency = tsnePoints[i][2];
        }
        currentIteration++;
        ofLog() << currentIteration;
    }
    
    ofAddListener(twister.eventEncoder, this, &ofApp::onEncoderUpdate);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    twister.update();
    
    ofPoint total;
    ofPoint center;
    
    total.set(0,0,0);
    
    for(int i = 0; i < dataPoints.size(); i++){
        
        dataPoints[i].transitionMillis = transitionMillis;
        dataPoints[i].update();
        mesh.getVertices()[i] = dataPoints[i].currentPoint;
        
        
        total.x += dataPoints[i].currentPoint.x;
        total.y += dataPoints[i].currentPoint.y;
        total.z += dataPoints[i].currentPoint.z;
        
    }
    
    center.x = total.x/dataPoints.size();
    center.y = total.y/dataPoints.size();
    center.z = total.z/dataPoints.size();
    
    
    if(prevCol1 != col1 ||
       prevCol2 != col2 ||
       prevCol3 != col3 ){
        
        for(int i = 0; i < dataPoints.size(); i++){
            if(i < (int)dataPoints.size()/3){
                dataPoints[i].color = col1;
            }
            else if(i >= (int)dataPoints.size()/3 && i < int(dataPoints.size()/3)*2){
                dataPoints[i].color = col2;
            }
            else if(i >= int(dataPoints.size()/3) * 2){
                dataPoints[i].color = col3;
            }
        }
    }
    
    
    
    
    
    cam.orbit(camLat+=camRotSpeedLat, camLon+=camRotSpeedLon, camDistance, center);
    cam.lookAt(center);
    cam.setFov(fov);
    
    light2.setAmbientColor(ofFloatColor(pointAmb));
    light2.setDiffuseColor(ofFloatColor(pointDiff));
    light.setAmbientColor(ofFloatColor(ambAmb));
    light.setDiffuseColor(ofFloatColor(ambDiff));
    
    
//    depthOfField.setFocalDistance(center.distance(cam.getPosition()));
    depthOfField.setFocalDistance(ofMap(sin(ofGetElapsedTimef()/2),-1,1, 20, 150));
    depthOfField.setFocalDistance(focusDistance);
    depthOfField.setFocalRange(aperture);
    depthOfField.setBlurAmount(blurAmount);
    if(bAutoFocus){
        setFocalPoint(center);
    }
    
    light2.setPosition(center);

    
    //set up indices
    mesh.clearIndices();
    mesh.clearColors();
    
    //update the dataPoint, lerp
    for(int a = 0; a < dataPoints.size(); a++){
    
        ofVec3f verta = mesh.getVertex(a);
        for(int b = a + 1; b < dataPoints.size(); b++){
            ofVec3f vertb = mesh.getVertex(b);
            int distance = (int)verta.distance(vertb);
            if (distance <= distanceThresh) {
                // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
                // connected to form a line
                mesh.addIndex(a);
                mesh.addIndex(b);

//                mesh.addColor(dataPoints[a].color);
//                mesh.addColor(dataPoints[b].color);
            }
        }
    }
    
    

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(bgColor);
    ofEnableLighting();
    ofEnableDepthTest();
    
//    depthOfField.begin();
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    cam.begin();
    
    light.enable();
    light2.enable();
    ofSetColor(meshCol);
    mesh.draw();
    
    ofSetLineWidth(1);

    for (int i=0; i<dataPoints.size(); i++) {
        float x = dataPoints[i].currentPoint.x;
        float y = dataPoints[i].currentPoint.y;
        float z = dataPoints[i].currentPoint.z;
        ofSetColor(dataPoints[i].color);
        ofDrawSphere(x, y, z, rad);
        
    }
    
    cam.end();
//    depthOfField.end();
//    
//    if(ofGetKeyPressed('f')){
//        depthOfField.drawFocusAssist(0, 0);
//    }
//    else{
//        depthOfField.getFbo().draw(0, 0);
//    }
    
    syphon.publishScreen();
    
    ofDisableLighting();
    ofDisableDepthTest();
    gui.draw();
    
    
    stringstream ss;
    ss << "num indices: " << mesh.getNumIndices() << endl
    << "num colors: " << mesh.getNumColors();
    ofDrawBitmapStringHighlight(ss.str(), 10, gui.getHeight() + 10);
}


void ofApp::reset(){
//    vector<vector<float>> data;
//    vector<float> tempData;
//    
//    for (int i = 0 ; i < dataPoints.size(); i++) {
//        tempData.push_back(dataPoints[i].numChildren);
//        tempData.push_back(dataPoints[i].bath);
//        tempData.push_back(dataPoints[i].watchTV);
//        tempData.push_back(dataPoints[i].drinkAlcohol);
//        tempData.push_back(dataPoints[i].read);
//        tempData.push_back(dataPoints[i].sleepQuality);
//        
//        data.push_back(tempData);
//        tempData.clear();
//    }
//    
//    int dims = 3;
//    float perplexity = 40;
//    float theta = 0.2;
//    bool normalize = true;
//    
//    tsnePoints = tsne.run(data ,dims,perplexity,theta,normalize, runManually);
    for(auto& d : dataPoints){
        d.pointIndex = 0;
    }
    
    
    
}

void ofApp::onEncoderUpdate(ofxMidiFighterTwister::EncoderEventArgs & a){
    ofLogNotice() << "Encoder '" << a.ID << "' Event! val: " << a.value;
    
    if(a.ID == 0){
        rad = ofMap(a.value, 0, 127, 1.0, 60);
    } else if(a.ID == 1){
        distanceThresh = ofMap(a.value, 0, 127, 1.0, 200);
    } else if(a.ID == 3){
        transitionMillis = ofMap(a.value, 0, 127, 100, 2000);
    } else if(a.ID == 2){
        meshCol = ofMap(a.value, 0, 127, 0.0, 1.0);
    } else if(a.ID == 4){
        camDistance = ofMap(a.value, 0, 127, 0, 7000);
    } else if(a.ID == 5){
        camRotSpeedLat = ofMap(a.value, 0, 127, 0.01, 2.0);
    } else if(a.ID == 6){
        camRotSpeedLon = ofMap(a.value, 0, 127, 0.01, 2.0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


void ofApp::setFocalPoint(ofVec3f point){
    float distance = cam.getPosition().distance(point);
    
    focusDistance = ((5.2*pow(10,-5)) * (distance * distance)) + (0.25 * distance) + 0.227414;
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
