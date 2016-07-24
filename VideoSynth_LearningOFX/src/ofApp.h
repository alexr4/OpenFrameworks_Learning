#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		//Add first GUI
		ofxPanel gui;
		ofxIntSlider countX;
		ofxFloatSlider stepX;
		ofxFloatSlider twistX;
		ofxFloatSlider scale;
		ofxIntSlider countY;
		ofxFloatSlider stepY, twistY;

		//add gui group for global
		ofxGuiGroup globalGroup;
		ofxFloatSlider globalScale;
		ofxFloatSlider globalRotation;
		ofxFloatSlider globalBackground;

		//add gui group for primitives
		ofxGuiGroup primGroup;
		ofxFloatSlider shiftY, rotate;
		ofxVec2Slider size;
		ofxColorSlider color;
		ofxToggle filled, type;

		//add gui group for mixing layers
		ofxGuiGroup mixerGroup;
		ofxFloatSlider imageAlpha, videoAlpha, cameraAlpha;

		//add gui to deform sphere shape
		ofxGuiGroup shapeDeformer;
		ofxFloatSlider radius, deform, deformFreq, extrude;

		//add gui for final fbo mixer
		ofxGuiGroup fboMixer;
		ofxFloatSlider show2d, show3d;

		//various variable
		bool showGui;
		ofTexture imgMichel; //object intended to draw image only (not manipulate pixels)
		ofVideoPlayer skyfall;
		float imageRes, videoRes;
		ofVideoGrabber camera;

		//FBO & Shaders
		ofFbo fbo, fbo2, fbo3;
		ofShader shader;
		ofxToggle kenable;
		ofxIntSlider ksector;
		ofxFloatSlider kangle, kx, ky;

		//3D objects
		ofSpherePrimitive sphere;
		ofEasyCam cam;
		ofLight light, light2;
		ofMaterial material;
		vector<ofPoint> originalVerticesList;

		//animation
		ofxToggle automate;
		float phase, frequency;

		//sound
		ofSoundPlayer sound;
		float soundLevel;

		//read fil
		ofFile file;
		ofBuffer buffer;

		//methods
		void setup();
		void update();
		void draw();
		void exit();
		//custom methods
		void stripePattern();
		void initParameters();
		void matrixPattern();
		void loadAssets();
		void videoMixer();
		void initBuffers();
		void initShaders();
		void bindToKaleido();
		void draw2D();
		void init3DObjects();
		void draw3D();
		void camOrbit();
		void deformShape();
		void animate();
		void initAnimationParameters();
		void initSound();
		void analyseSound();
		void audioIn(float *input, int buffersize, int nChannels);
		void initFiles();
		void readData();

		//events and interaction 
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

};
