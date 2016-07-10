#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("ofx_learning_VideoSynth");
	ofSetWindowShape(1280, 720);
	//ofSetVerticalSync(false);//if true = lock the FPS to the GPU/CPU refresh Rate
	ofSetFrameRate(60);
	ofBackground(ofColor::white);//create a random color : ofColor(ofRandom( 0, 255 ), ofRandom( 0, 255 ), ofRandom( 0, 255 ))
	//Background is call once on the setup then automacally repeated on the draw fonction. To disable the background redrawing use : ofSetBackgroundAuto(false)
	//ofSetFullscreen(true);
	//ofEnableSmoothing(); //only work on stroke

	initParameters();
	loadAssets();
	initBuffers();
	initShaders();
}

void ofApp::initShaders() {
	shader.load("kaleido");
}

void ofApp::initBuffers() {
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);

	ofSetLogLevel(OF_LOG_VERBOSE);
	fbo.checkGLSupport();
}

void ofApp::loadAssets(){
	ofLoadImage(imgMichel, "michel.jpg"); //load texture
	skyfall.loadMovie("skyfall.mp4"); //load video
	skyfall.play(); //play it

	imageRes = imgMichel.getWidth() / imgMichel.getHeight();
	videoRes = skyfall.getWidth() / skyfall.getHeight();
}

void ofApp::initParameters() {
	//define gui
	gui.setup("Parameters", "settings.xml");
	gui.add(countX.setup("countX", 200, 0, 200));
	gui.add(stepX.setup("stepX", 20, 0, 200));
	gui.add(twistX.setup("twistX", 0, -45, 45));
	gui.add(scale.setup("scale", 1, -10, 10));
	gui.add(countY.setup("CountY", 1, 0, 100));
	gui.add(stepY.setup("StepY", 20, 0, 200));
	gui.add(twistY.setup("TwistY", 0, -90, 90));
	
	//add a group for globals
	globalGroup.setup("Global");
	globalGroup.add(globalScale.setup("Scale", 1, 0.0, 1));
	globalGroup.add(globalRotation.setup("Rotate", 0, -180, 180));
	globalGroup.add(globalBackground.setup("Background", 255, 0, 255));
	gui.add(&globalGroup);

	//add group for primitives
	primGroup.setup("Primitive");
	primGroup.add(shiftY.setup("ShiftY", 0.0, -1000.0, 1000.0));
	primGroup.add(rotate.setup("Rotate", 0.0, -180.0, 180));
	primGroup.add(size.setup("Size", ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(10, 10)));
	primGroup.add(color.setup("Color", ofColor::black, ofColor(0, 0, 0, 0), ofColor::white));
	primGroup.add(filled.setup("Filled", false));
	primGroup.add(type.setup("Type", false));
	gui.add(&primGroup);

	//add group for mixing layer
	mixerGroup.setup("Mixer");
	mixerGroup.setHeaderBackgroundColor(ofColor::darkBlue);
	mixerGroup.setBorderColor(ofColor::green);
	mixerGroup.add(imageAlpha.setup("Image Alpha", 100, 0, 255));
	mixerGroup.add(videoAlpha.setup("Video Alpha", 100, 0, 255));
	mixerGroup.add(cameraAlpha.setup("Camera Alpha", 100, 0, 255));
	mixerGroup.add(kenable.setup("Enable Kaleidoscope", true));
	mixerGroup.add(ksector.setup("Num. of Sector", 10, 1, 250));
	mixerGroup.add(kangle.setup("Angle", 0, -180, 180));
	mixerGroup.add(kx.setup("Kx", 0.5, 0, 1));
	mixerGroup.add(ky.setup("Ky", 0.5, 0, 1));
	gui.minimizeAll();//minimize all other groups
	gui.add(&mixerGroup);

	//load saved parameters
	gui.loadFromFile("settings.xml");
	showGui = true;
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle("FPS : "+ofToString(ofGetFrameRate()));

	skyfall.update();//update video playing (get next frame)

	//grabb video from camera
	if (camera.isInitialized())
	{
		camera.update();
	}

}

void ofApp::stripePattern() {
	//ofLog(OF_LOG_NOTICE, "Hello World");
	ofColor c = ofColor::black;
	//ofSetColor(color);
	if (filled)
	{
		ofFill();
	}
	else
	{
		ofNoFill();
	}
	ofSetLineWidth(1.0);
	for (int i = 0; i < countX; i++) {
		ofPushMatrix();
		ofTranslate((-countX/2 + i) * stepX, 0);
		ofRotate(ofMap(i, 0, 100, 0, 360.0) + twistX);

		c = ofColor::fromHsb(ofMap(i, 0, countX, 0, 255), 255, 255);
		ofColor tmp = *(&color);
		tmp.r = c.r + tmp.r;
		tmp.g = c.g + tmp.g;
		tmp.b = c.b + tmp.b;

		ofSetColor(tmp);

		ofPushMatrix();
		ofTranslate(0, shiftY);
		ofRotate(rotate);
		ofScale(size->x, size->y);
		if (type)
		{
			//draw rect
			ofRect(0, 0, 100 * scale, 100 * scale);
		}
		else {
			//draw triangles
			ofTriangle(-100 * scale, 100 * scale, 100 * scale, 100 * scale, 0 * scale, -100 * scale);
		}

		ofPopMatrix();

		//draw lines
		//ofLine(0, -100, 0, 100);
		ofPopMatrix();
	}
}

void ofApp::matrixPattern(){
	//First we move the origin coordinates from top-left to center of the windows
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	//add scale & rotation
	float scl = pow(globalScale, 4.0f);
	ofScale(scl, scl);
	ofRotate(globalRotation);

	for (int y = 1; y <= countY; y++)
	{
		ofPushMatrix();
		ofTranslate(0, (-countY / 2 + y) * stepY);
		ofRotate(y * twistY);
		stripePattern();
		ofPopMatrix();
	}

	//Define the color of the drawing
	//ofSetColor(ofColor::black);
	//ofFill();
	//ofNoFill();
	//Draw a line
	//ofSetLineWidth(10.0); //change line weight
	//ofLine(0, ofGetHeight() / 2 * -1, 0, ofGetHeight() / 2);

	//draw various primitives
	//ofSetRectMode(OF_RECTMODE_CENTER); //center rect : option are : OF_RECTMODE_CENTER & OF_RECTMODE_CORNER 
	//ofRect(0, 0, 200, 200);
	//ofTriangle(-100, 100, 100, 100, 0, -100);
	//ofSetCircleResolution(50); // by default a circle has 22 as a resolution
	//ofCircle(0, 0, 250);

	ofPopMatrix();
}

void ofApp::videoMixer(){
	//enable blending (alpha, add, screen, multiply, substract, disable);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofDisableSmoothing(); //disable smoothing for additive blending

	//disaply image
	ofSetColor(255, imageAlpha); //set to white in order to display image color correctly
								 //ofSetColor(ofColor::green);
	imgMichel.draw(0, ofGetHeight() / 2 - (ofGetWidth() / imageRes) / 2, ofGetWidth(), ofGetWidth() / imageRes);
	//display video
	ofSetColor(255, videoAlpha); //set to white in order to display image color correctly
	skyfall.draw(0, ofGetHeight() / 2 - (ofGetWidth() / videoRes) / 2, ofGetWidth(), ofGetWidth() / videoRes);
	//display camera
	if (camera.isInitialized())
	{
		ofSetColor(255, cameraAlpha);
		camera.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	//enable defaut alpha blending
	ofEnableAlphaBlending();
	ofEnableSmoothing();
}

void ofApp::bindToKaleido() {
	shader.setUniform1i("ksector", ksector);
	shader.setUniform1f("kangleRad", ofDegToRad(kangle));
	shader.setUniform2f("kcenter", kx * ofGetWidth(), ky * ofGetHeight());
	shader.setUniform2f("screenCenter", 0.5 * ofGetWidth(), 0.5 * ofGetHeight());
}

void ofApp::draw2D() {
	//add new background
	ofBackground(globalBackground);

	videoMixer();
	matrixPattern();

}

//--------------------------------------------------------------
void ofApp::draw(){

	//compute fbo
	fbo.begin();
	draw2D();
	fbo.end();
	//draw fbo with shaders
	if (kenable) {
		shader.begin();
		bindToKaleido();
	}
	//draw fbo
	ofSetColor(255);
	fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
	if (kenable) {
		shader.end();
	}


	//draw GUi
	if (showGui) {
		gui.draw();
	}
}

void ofApp::exit() {
	gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'g' || key == 'G') {
		showGui = !showGui;
	}
	if (key == OF_KEY_RETURN) {
		int time = ofGetElapsedTimeMillis();
		ofSaveScreen("screenshot_"+ ofToString(time) + ".png");
	}
	if (key == 's' || key == 'S') {
		ofFileDialogResult res;
		res = ofSystemSaveDialog("preset.xml", "Saving preset");
		if (res.bSuccess)
		{
			gui.saveToFile(res.filePath);
		}
	}
	if (key == 'l' || key == 'L')
	{
		ofFileDialogResult res;
		res = ofSystemLoadDialog("Loading Preset");
		if (res.bSuccess)
		{
			gui.loadFromFile(res.filePath);
		}
	}
	if (key == 'c' || key == 'C')
	{
		ofSetLogLevel(OF_LOG_VERBOSE);
		camera.listDevices();
		camera.setDeviceID(0);
		camera.setDesiredFrameRate(30);
		camera.initGrabber(1280, 720);
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
