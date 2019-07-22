//
//  stage.cpp
//  Yamamotosan_Simulation
//
//  Created by 村上航輔 on 2019/07/21.
//

#include "baseStage.h"
float baseStage::getTemperture() {
    return temperture;
}
//--------------------------------------------------------------
ofVec2f baseStage::getPosition() {
    return position;
}
//--------------------------------------------------------------
float baseStage::getWidth() {
    return width;
}
//--------------------------------------------------------------
float baseStage:: getHeight() {
    return height;
}
//--------------------------------------------------------------
void baseStage::setup(float temp, ofVec2f pos, float width, float height){
    this->temperture = temp;
    this->position = pos;
    this->width = width;
    this->height = height;
}

//--------------------------------------------------------------
void baseStage::update(float temp){
    this->temperture = temp;
}

//--------------------------------------------------------------
void baseStage::draw(float temperture){
    float alpha = ofMap(temperture, 0, 20, 0, 100);
    ofSetColor(255, 0, 0, alpha);
    ofDrawRectangle(position, width, height);
}

//--------------------------------------------------------------
void baseStage::keyPressed(int key){

}

//--------------------------------------------------------------
void baseStage::keyReleased(int key){
    
}

//--------------------------------------------------------------
void baseStage::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void baseStage::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void baseStage::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void baseStage::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void baseStage::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void baseStage::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void baseStage::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void baseStage::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void baseStage::dragEvent(ofDragInfo dragInfo){
    
}
