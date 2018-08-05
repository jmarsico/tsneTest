//
//  directionalLight.hpp
//  NW-MUTUAL
//
//  Created by Ultra Low Res Studuio on 9/22/17.
//
//

#ifndef directionalLight_hpp
#define directionalLight_hpp

#include <stdio.h>
#include "ofMain.h"

class DirectionaLight{
public:
    DirectionaLight();
    void init(int id);
    void update();
    void draw();
    
    ofLight l;
    ofVec3f lookAt;
    ofParameterGroup params;
    ofParameter<float> amb;
    
    
};

#endif /* directionalLight_hpp */
