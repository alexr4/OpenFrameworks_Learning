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

		//various variable
		bool showGui;
		ofTexture imgMichel; //object intended to draw image only (not manipulate pixels)
		ofVideoPlayer skyfall;
		float imageRes, videoRes;
		ofVideoGrabber camera;

		//FBO & Shaders
		ofFbo fbo;
		ofShader shader;
		ofxToggle kenable;
		ofxIntSlider ksector;
		ofxFloatSlider kangle, kx, ky;

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
