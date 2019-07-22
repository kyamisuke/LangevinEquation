#include "particle.h"
#include "ofMain.h"
//#define OF_ADDON_USING_OFXVECTORMATH
//#include "ofAddons.h"

//------------------------------------------------------------
particle::particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.07f;
	bFixed = false;
    jointNum = 0;
    for (int j=0; j < 3; j++) {
        jointPos[j] = 999;
    }
}

//------------------------------------------------------------
void particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y, float stringConstant){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x * stringConstant;
    frc.y = frc.y + y * stringConstant;
}

void particle::addRepulsiveForce(float x, float y, float stringConstant){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x * stringConstant;
    frc.y = frc.y + y * stringConstant;
}
//------------------------------------------------------------
void particle::updateJointNum() {
    if (jointNum < 3) { jointNum++; }
}
//------------------------------------------------------------
void particle::resetJointNum() {
    jointNum = 0;
}
//------------------------------------------------------------
//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void particle::update(float temperture, float viscocity, float timeInterval){
	
	if (bFixed == false){
        pos.x = pos.x + frc.x*timeInterval/viscocity + pow(temperture*timeInterval/viscocity, 0.5)*normRandom(0., 1.);
        if (pos.x > ofGetWidth()) { pos.x -= ofGetWidth(); }
        else if (pos.x < 0) { pos.x += ofGetWidth(); }
        pos.y = pos.y + frc.y*timeInterval/viscocity + pow(temperture*timeInterval/viscocity, 0.5)*normRandom(0., 1.);
        if (pos.y > ofGetHeight()) { pos.y -= ofGetHeight(); }
        else if (pos.y < 0) { pos.y += ofGetHeight(); }
	}
}
//------------------------------------------------------------
float particle::normRandom(float m, float s) {
    float a = 1 - ofRandom(1);
    float b = 1 - ofRandom(1);
    float c = sqrt(-2 * log(a));
    if (0.5 - ofRandom(1) > 0) {
        return c * sin(2*b*3.14159265) * s + m;
    } else {
        return c * cos(2*b*3.14159265) * s + m;
    }
}
//------------------------------------------------------------
void particle::draw(){
    ofDrawCircle(pos.x, pos.y, 3);
}
//------------------------------------------------------------

