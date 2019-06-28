#include "ofApp.h"

ofVec2f ofApp::getGravity(vector <particle> particles) {
    ofVec2f sum = ofVec2f(0, 0);
    for (particle& p : particles) {
        sum += p.pos;
    }
    
    return sum / particles.size();
}
//--------------------------------------------------------------
float ofApp::getAverage(vector <float> num) {
    float sum = 0.;
    for (float& n : num) {
        sum += n;
    }
    
    return sum / num.size();
}
//--------------------------------------------------------------
float ofApp::getDispersion(vector <float> num){
    float avg = getAverage(num);
    float sum = 0.;
    for (float& n : num) {
        sum += pow(avg - n, 2);
    }
    
    return sum / num.size();
}

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
    
    // graph setting
    for (int i=0; i < graphResolution; i++) {
        bgGraph.addVertex(ofVec3f(i*2, 480, 0));
        bgGraph.addColor(ofColor(0, 150, 0, 100));
    }
    bgGraph.setMode(OF_PRIMITIVE_LINE_STRIP);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i=0; i < ofGetWidth(); i+=div) {
        ofSetColor(150, 100);
        ofDrawLine(i, 0, i, ofGetHeight());
    }
    for (int i=0; i < ofGetHeight(); i+=div) {
        ofSetColor(150, 100);
        ofDrawLine(0, i, ofGetWidth(), i);
    }
    
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
    
    // check dispersion
    ofVec2f gravityPoint = getGravity(particles);
    vector <float> dists;
    float dispersion;
    for (auto& p : particles) {
        float dist = ofDist(p.pos.x, p.pos.y, gravityPoint.x, gravityPoint.y);
        dists.push_back(dist);
    }
    dispersion = getDispersion(dists);
    
    gui.draw();
    //if (ofGetFrameNum()%5 == 0) {
        for (int i=0; i < bgGraph.getVertices().size(); i++) {
            if (i < bgGraph.getVertices().size()-1) {
                bgGraph.setVertex(i, ofVec3f(i*2, bgGraph.getVertex(i+1).y, 0));
            } else {
                bgGraph.setVertex(i, ofVec3f(i*2, 360-(dispersion-6200)/10, 0));
            }
        }
    //}
    bgGraph.draw();
    
    // debug: display now frame per second
    ofSetColor(39);
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 10, 100);
    ofDrawBitmapString("gravity point: (" + ofToString(gravityPoint.x) + ", " + ofToString(gravityPoint.y) + ")", 10, 110);
    ofDrawBitmapString("dispersion: " + ofToString(dispersion), 10, 120);
    for (int i=0; i < ofGetHeight(); i+=div) {
        ofDrawBitmapString(ofToString((i-360)*10+6200), ofGetWidth()-40, ofGetHeight()-i);
    }
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
        for (int i=0; i < graphResolution; i++) {
            bgGraph.setVertex(i, ofVec3f(i*2, 480, 0));
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
