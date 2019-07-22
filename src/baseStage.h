//
//  stage.h
//  Yamamotosan_Simulation
//
//  Created by 村上航輔 on 2019/07/21.
//

#ifndef stage_h
#define stage_h


#endif /* stage_h */

#pragma once

#include "ofMain.h"

class baseStage {
    
public:
    void setup(float temp, ofVec2f pos, float width, float height);
    void update(float temp);
    void draw(float temperture);
    
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
    
    float getTemperture();
    ofVec2f getPosition();
    float getWidth();
    float getHeight();
    
    float temperture;
    ofVec2f position;
    float width, height;
};

