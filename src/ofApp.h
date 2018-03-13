#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxTSNE.h"
#include "ofxSyphon.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void reset();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofxTSNE tsne;
    ofxCsv csvLoader;
    
    struct sleepDataPoint {
        int numChildren;
        int watchTV;
        int drinkAlcohol;
        int read;
        int bath;
        int sleepQuality;
        ofPoint tsnePoint;
        int color;
        float tsneTransparency; 
    };
    
    ofxPanel gui;
    ofParameter<float> distanceThresh;
    ofParameter<float> rad;
    ofParameter<float> meshCol;
    
    vector<sleepDataPoint> dataPoints;
    vector<vector<double>> tsnePoints;
    
    ofEasyCam cam;
    
    
    ofMesh mesh;
    
    bool runManually;
    
    ofLight light;
    
    ofxSyphonServer syphon;
};
