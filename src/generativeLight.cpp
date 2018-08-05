//
//  generativeLight.cpp
//  abstractions
//
//  Created by Jakob Marsico on 7/12/16.
//
//

#include "generativeLight.h"

//--------------------------------------------------------------
void GenerativeLight::init(int ID, ofxColorGradient<ofColor>* _colors, ofBoxPrimitive* _bBox){
   
    width = ofGetWidth();
    height = ofGetHeight();
    string name = "light ";
    name.append(ofToString(ID));
    params.setName(name);
    params.add(bNoiseMotion.set("noise motion", false));
    params.add(noiseSpeed.set("noise speed", 0.01, 0.0001, 0.1));
    colors = _colors;
    
    params.add(col.set("Color0", 0, 0, 5));
    params.add(transX.set("Trans X", width/2.0, 0.0, width));
    params.add(transY.set("Trans Y", width/2.0, 0.0, height));
    params.add(transZ.set("Trans Z", 100.0, -500.0, 500.0));
    params.add(lookAtX.set("look at X", width/2.0, 0.0, width));
    params.add(lookAtY.set("look at Y", height/2.0, 0.0, height));
    params.add(lookAtZ.set("look at Z", 100.0, -500.0, 500.0));
    params.add(spec.set("Spec 0", 0.5, 0.0, 1.0));
    params.add(diff.set("Diff 0", 0.5, 0.0, 1.0));
    params.add(amb.set("Amb 0", 0.5, 0.0, 1.0));
    params.add(att.set("Att 0", 0.5, 0.0, 1.0));

    
    
    light.setup();
    light.setPointLight();
    light.lookAt(ofVec3f(lookAtZ, lookAtY, lookAtZ));
    light.setAmbientColor(ofFloatColor(amb));
    light.setAttenuation(att, 0.0001, 0.0001);
    light.setDiffuseColor(ofFloatColor(diff));
    light.setSpecularColor(ofFloatColor(spec));
    light.setAmbientColor(ofFloatColor(amb));
    light.setPosition(transX,transY,transZ);
    
    xNoiseCounter = ofRandom(0.1);
    yNoiseCounter = ofRandom(0.1);
    zNoiseCounter = ofRandom(0.1);
    

    
    bBox = _bBox;
    
}


//--------------------------------------------------------------
void GenerativeLight::update(){
    
    
    if(bNoiseMotion){
        transX = ofMap(ofNoise(xNoiseCounter), 0.f, 1.f, bBox->getPosition().x - bBox->getWidth()/2,  bBox->getPosition().x + bBox->getWidth()/2);
        transY = ofMap(ofNoise(yNoiseCounter), 0.f, 1.f, bBox->getPosition().y - bBox->getHeight()/2,  bBox->getPosition().y + bBox->getHeight()/2);
        transZ = ofMap(ofNoise(zNoiseCounter), 0.f, 1.f, bBox->getPosition().z - bBox->getDepth()/2,  bBox->getPosition().z + bBox->getDepth()/2);;
        light.resetTransform();
        
        
        xNoiseCounter += noiseSpeed + 0.001;
        yNoiseCounter += noiseSpeed + 0.0001;
        zNoiseCounter += noiseSpeed;
        
    }
    
    light.setPosition(transX,transY,transZ);
    
    
    light.setAmbientColor(chooseColor(col)*=amb);
    light.setAttenuation(att, 0.0001, 0.0001);
    light.setDiffuseColor(chooseColor(col)*=diff);
    light.setSpecularColor(chooseColor(col)*=spec);
    light.lookAt(ofVec3f(lookAtX, lookAtY, lookAtZ));
    
    

}

void GenerativeLight::draw(){
    ofSetColor(255);
    light.draw();

}

//--------------------------------------------------------------
ofFloatColor GenerativeLight::chooseColor(int color){
    
    
    ofFloatColor c;
    switch (color) {
        case 0:
            c.set(1.0, 1.0, 1.0);
            break;
        case 1:
            c = ofColor::fromHex(0xE77D6E);
            break;
        case 2:
            c = ofColor::fromHex(0x3DEBBD);
            break;
        case 3:
            c = ofColor::fromHex(0x3C5F95);
            break;
        case 4:
            c = ofColor::fromHex(0xA453AE);
            break;
        case 5:
            c = ofColor::fromHex(0x162365);
            break;
    }
    
    return c;
}
