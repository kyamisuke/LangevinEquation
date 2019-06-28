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
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		
		void addRepulsionForce(particle &p, float radius, float scale);
		void addAttractionForce(particle &p, float radius, float scale);
		void addClockwiseForce(particle &p, float radius, float scale);
		void addCounterClockwiseForce(particle &p, float radius, float scale);
    void updateJointNum();
    void resetJointNum();
	
		
		void addDampingForce();
        
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
