#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(239);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    // parameter
    gui.setup();
    gui.setPosition(10, 10);
    gui.add(temperture.set("temperture", 1.0, 0.0, 5.0));
    gui.add(viscocity.set("viscocity", 1.0, 1.0, 3.0));
    gui.add(timeInterval.set("timeInterval", 0.1, 0.0, 0.1));
    
    int particleNum = 104;
    for (int i=0; i < particleNum; i++) {
        particle p = particle();
        particles.push_back(p);
    }
    
    // initial condition
    for (int i=0; i<2; i++) {
        for (int j=0; j<6; j++) {
            particles[i*6+j].pos = ofVec2f(100+104*j, 30+120*i);
        }
    }
    for (int i=0; i<2; i++) {
        for (int j=0; j<6; j++) {
            particles[12+i*6+j].pos = ofVec2f(100+104*j, 210+120*i);
        }
    }
    for (int i=0; i<2; i++) {
        for (int j=0; j<6; j++) {
            particles[24+i*6+j].pos = ofVec2f(100+104*j, 390+120*i);
        }
    }
    for (int i=0; i<2; i++) {
        for (int j=0; j<6; j++) {
            particles[36+i*6+j].pos = ofVec2f(100+104*j, 570+120*i);
        }
    }
    for (int i=0; i<2; i++) {
        for (int j=0; j<7; j++) {
            particles[48+i*7+j].pos = ofVec2f(48+104*j, 60+60*i);
        }
    }
    for (int i=0; i<2; i++) {
        for (int j=0; j<7; j++) {
            particles[62+i*7+j].pos = ofVec2f(48+104*j, 240+60*i);
        }
    }
    for (int i=0; i<2; i++) {
        for (int j=0; j<7; j++) {
            particles[76+i*7+j].pos = ofVec2f(48+104*j, 420+60*i);
        }
    }
    for (int i=0; i<2; i++) {
        for (int j=0; j<7; j++) {
            particles[90+i*7+j].pos = ofVec2f(48+104*j, 600+60*i);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // segment
    for (int i=0; i<particles.size(); i++) {
        for (int j=i; j<particles.size(); j++) {
            ofVec2f pos_i = particles[i].pos;
            ofVec2f pos_j = particles[j].pos;
            float dist = ofDist(pos_i.x, pos_i.y, pos_j.x, pos_j.y);
            int i_num = particles[i].segmentNum;
            int j_num = particles[j].segmentNum;
            if (i_num == 3 || j_num == 3) { continue; }
            
            if (dist >= 1 && dist <= 80) {
                ofSetColor(39);
                ofDrawLine(pos_i, pos_j);
                particles[i].updateSegmentNum();
                particles[j].updateSegmentNum();
                particles[i].segmentPos[i_num] = j;
                particles[j].segmentPos[j_num] = i;
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
            
            if (particles[i].segmentPos[0] == j || particles[i].segmentPos[1] == j
                || particles[i].segmentPos[2] == j) {
                if (dist >= 1 && dist <= 60) {
                    dir_ji *= abs(60 - dist);
                    particles[i].addForce(dir_ji.x, dir_ji.y);
                    particles[j].addForce(-dir_ji.x, -dir_ji.y);
                }else if (dist > 60 && dist <= 80) {
                    dir_ji *= abs(60 - dist);
                    particles[i].addForce(-dir_ji.x, -dir_ji.y);
                    particles[j].addForce(dir_ji.x, dir_ji.y);
                }
            } else {
                if (dist >= 1 && dist <= 60) {
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
        int num = particles[i].segmentNum;
        ofSetColor(num*80, 50, 240-num*80);
        particles[i].draw();
        particles[i].resetSegmentNum();
        particles[i].resetForce();
        for (int j=0; j < 3; j++) {
            particles[i].segmentPos[j] = 999;
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
        for (int i=0; i<2; i++) {
            for (int j=0; j<6; j++) {
                particles[i*6+j].pos = ofVec2f(100+104*j, 30+120*i);
            }
        }
        for (int i=0; i<2; i++) {
            for (int j=0; j<6; j++) {
                particles[12+i*6+j].pos = ofVec2f(100+104*j, 210+120*i);
            }
        }
        for (int i=0; i<2; i++) {
            for (int j=0; j<6; j++) {
                particles[24+i*6+j].pos = ofVec2f(100+104*j, 390+120*i);
            }
        }
        for (int i=0; i<2; i++) {
            for (int j=0; j<6; j++) {
                particles[36+i*6+j].pos = ofVec2f(100+104*j, 570+120*i);
            }
        }
        for (int i=0; i<2; i++) {
            for (int j=0; j<7; j++) {
                particles[48+i*7+j].pos = ofVec2f(48+104*j, 60+60*i);
            }
        }
        for (int i=0; i<2; i++) {
            for (int j=0; j<7; j++) {
                particles[62+i*7+j].pos = ofVec2f(48+104*j, 240+60*i);
            }
        }
        for (int i=0; i<2; i++) {
            for (int j=0; j<7; j++) {
                particles[76+i*7+j].pos = ofVec2f(48+104*j, 420+60*i);
            }
        }
        for (int i=0; i<2; i++) {
            for (int j=0; j<7; j++) {
                particles[90+i*7+j].pos = ofVec2f(48+104*j, 600+60*i);
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
