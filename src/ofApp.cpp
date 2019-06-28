#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(239);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    // parameter
    gui.setup();
    gui.setPosition(10, 10);
    gui.add(temperture.set("temperture", 10.0, 0.0, 40.0));
    gui.add(viscocity.set("viscocity", 1.0, 1.0, 5.0));
    gui.add(timeInterval.set("timeInterval", 0.1, 0.0, 0.1));
    
    int particleNum = 204;
    for (int i=0; i < particleNum; i++) {
        particle p = particle();
        particles.push_back(p);
    }
    
    // initial condition
    for (int i=0; i<6; i++) {
        for (int j=0; j<17; j++) {
            particles[j+i*17].pos = ofVec2f(150+j*26, 150-(j%2)*15+90*i);
        }
    }
    
    for (int i=0; i<6; i++) {
        for (int j=0; j<17; j++) {
            particles[102+j+i*17].pos = ofVec2f(150+j*26, 180+(j%2)*15+90*i);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // joint
    for (int i=0; i<particles.size(); i++) {
        for (int j=i; j<particles.size(); j++) {
            ofVec2f pos_i = particles[i].pos;
            ofVec2f pos_j = particles[j].pos;
            float dist = ofDist(pos_i.x, pos_i.y, pos_j.x, pos_j.y);
            int i_num = particles[i].jointNum;
            int j_num = particles[j].jointNum;
            if (i_num == 3 || j_num == 3) { continue; }
            
            if (dist >= 1 && dist <= 40) {
                ofSetColor(39);
                ofDrawLine(pos_i, pos_j);
                particles[i].updateJointNum();
                particles[j].updateJointNum();
                particles[i].jointPos[i_num] = j;
                particles[j].jointPos[j_num] = i;
            }
        }
    }
    
    // calculate potential
    for (int i=0; i<particles.size(); i++) {
        for (int j=i; j<particles.size(); j++) {
            ofVec2f pos_i = particles[i].pos;
            ofVec2f pos_j = particles[j].pos;
            ofVec2f dir_ji = pos_i - pos_j;
            dir_ji.normalize();
            float dist = ofDist(pos_i.x, pos_i.y, pos_j.x, pos_j.y);
            
            if (particles[i].jointPos[0] == j || particles[i].jointPos[1] == j
                || particles[i].jointPos[2] == j) {
                if (dist >= 1 && dist <= 30) {
                    dir_ji *= abs(60 - dist);
                    particles[i].addForce(dir_ji.x, dir_ji.y);
                    particles[j].addForce(-dir_ji.x, -dir_ji.y);
                }else if (dist > 30 && dist <= 40) {
                    dir_ji *= abs(60 - dist);
                    particles[i].addForce(-dir_ji.x, -dir_ji.y);
                    particles[j].addForce(dir_ji.x, dir_ji.y);
                }
            } else {
                if (dist >= 1 && dist <= 30) {
                    dir_ji *= abs(60 - dist);
                    particles[i].addForce(dir_ji.x, dir_ji.y);
                    particles[j].addForce(-dir_ji.x, -dir_ji.y);
                }
            }
            
        }
        particles[i].update(temperture, viscocity, timeInterval);
    }
    
    // draw particle
    for (int i=0; i<particles.size(); i++) {
        int num = particles[i].jointNum;
        ofSetColor(num*80, 50, 240-num*80);
        particles[i].draw();
        particles[i].resetJointNum();
        particles[i].resetForce();
        for (int j=0; j < 3; j++) {
            particles[i].jointPos[j] = 999;
        }
    }
    
    gui.draw();
    
    // debug: display now frame per second
    ofSetColor(39);
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 10, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') { // press space bar -> reset
        for (int i=0; i<6; i++) {
            for (int j=0; j<17; j++) {
                particles[j+i*17].pos = ofVec2f(150+j*26, 150-(j%2)*15+90*i);
            }
        }
        
        for (int i=0; i<6; i++) {
            for (int j=0; j<17; j++) {
                particles[102+j+i*17].pos = ofVec2f(150+j*26, 180+(j%2)*15+90*i);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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
