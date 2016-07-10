#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context
	/*ofGLWindowSettings settings;
	settings.width = 1280;
	settings.height = 720;
	settings.setGLVersion(4, 5); /// < select your GL Version here
	settings.windowMode = OF_WINDOW;
	ofCreateWindow(settings); ///< create your window here
	*/
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
