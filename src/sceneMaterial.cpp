//
//  sceneMaterial.cpp
//  NW-MUTUAL
//
//  Created by Ultra Low Res Studuio on 10/14/17.
//
//

#include "sceneMaterial.h"

void SceneMaterial::init(string name){
    params.setName(name);
    params.add(shininess.set("Shininess", 1.0, 0.0, 10.0));
    params.add(spec.set("Specular", 0.5, 0.0, 1.0));
    params.add(diffuse.set("Diffuse", 0.5, 0.0, 1.0));
    params.add(ambient.set("Ambient", 0.5, 0.0, 1.0));

    
}

void SceneMaterial::update(ofColor c){
    material.setAmbientColor(ofColor(c.r * ambient, c.g * ambient, c.b * ambient));
    material.setDiffuseColor(ofColor(c.r * diffuse, c.g * diffuse, c.b * diffuse));
    material.setSpecularColor(ofColor(c.r * spec, c.g * spec, c.b * spec));
    material.setShininess(shininess);
    
}

void SceneMaterial::begin(){
    material.begin();
}

void SceneMaterial::end(){
    material.end();
}
