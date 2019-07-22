#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"
#define OF_ADDON_USING_OFXVECTORMATH
//#include "ofAddons.h"

class particle
{
    public:
        ofVec2f pos;
        ofVec2f vel;
        ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
			
        particle();
		virtual ~particle(){};

        void resetForce();
		void addForce(float x, float y, float stirngConstant);
    void addRepulsiveForce(float x, float y, float stirngConstant);
    void updateJointNum();
    void resetJointNum();
	
		void setInitialCondition(float px, float py, float vx, float vy);
        void update(float temperture, float viscocity, float timeInterval);
        void draw();
    float normRandom(float m, float s);
	
		void bounceOffWalls();
	
		bool  bFixed;
	
		float damping;
    
    int jointNum;
    
    int jointPos[3];
    vector <float> jointDis;

    protected:
    private:
};

#endif // PARTICLE_H
