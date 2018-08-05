//
//  sceneMaterial.hpp
//  NW-MUTUAL
//
//  Created by Ultra Low Res Studuio on 10/14/17.
//
//

#ifndef sceneMaterial_hpp
#define sceneMaterial_hpp

#include <stdio.h>
#include "ofMain.h"

class SceneMaterial {
public:
    SceneMaterial(){};
    void init(string name);
    void update(ofColor c);
    void begin();
    void end();
    
    
    ofParameterGroup params;
    ofParameter<float> shininess;
    ofParameter<float> spec;
    ofParameter<float> diffuse;
    ofParameter<float> ambient;
    
    ofMaterial material;
};

#endif /* sceneMaterial_hpp */
