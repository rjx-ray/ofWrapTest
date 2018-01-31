#include "ofApp.h"
#include "ofUtils.h"

//--------------------------------------------------------------
void ofApp::setup() {

	loadSettings();
	
	ofSetFrameRate(setFPS);
	ofSetVerticalSync(vsync);

	//font.loadFont("GUI/Verdana.ttf", 36, true, true);

	ofFbo::Settings fboSettings = ofFbo::Settings();
	fboSettings.width = fboWidth;
	fboSettings.height = fboHeight;
	fboSettings.internalformat = GL_RGBA;
	fboSettings.wrapModeHorizontal = GL_REPEAT;
	fboSettings.wrapModeVertical = GL_REPEAT;
	fboSettings.textureTarget = GL_TEXTURE_2D;
	canvasFBO.allocate(fboSettings);
	outputFBO.allocate(fboSettings);

	loaded = currentImage.load(fileName);
	if (fullScreen) ofSetFullscreen(fullScreen);

	accumulateStartTime = ofGetElapsedTimef();
	lastDrawTime = ofGetElapsedTimef();
	drawCount = 0;

}

//--------------------------------------------------------------
void ofApp::update(){	

}

//--------------------------------------------------------------
void ofApp::draw() {

	// Do fps calculations
	drawCount++;
	float timeAccumulated  = ofGetElapsedTimef() - accumulateStartTime;
	if (timeAccumulated >= 0.5) {
		timeBetweenDraws = timeAccumulated / drawCount;
		measuredFps = 1 / timeBetweenDraws;
		ofFps = ofGetFrameRate();
		drawCount = 0;
		accumulateStartTime = ofGetElapsedTimef();
	}

	// Do wrap calculations
	float timeNow = ofGetElapsedTimef(); 
	float timeSinceLastDraw = timeNow - lastDrawTime;
	lastDrawTime = timeNow;
	if (wrapRate != 0) wrapAmount = wrapAmount + (wrapRate * timeSinceLastDraw);
	else wrapAmount = 0;
	if (wrapAmount > 1 || wrapAmount < -1) wrapAmount = 0;


	canvasFBO.begin();
		ofClear(0, 0, 0);
		ofBackground(0, 0, 0);
		if (loaded) currentImage.draw(0, 0, fboWidth, fboHeight);
		else ofDrawBitmapString("No image loaded", 100, 100);
	canvasFBO.end();
	
	int xPos = wrapAmount * fboWidth;
	outputFBO.begin();
		ofClear(0, 0, 0);
		ofBackground(0, 0, 0);
		canvasFBO.getTextureReference().drawSubsection(0, 0, fboWidth, fboHeight, xPos, 0);
	outputFBO.end();
	
	outputFBO.draw(0, 0, winWidth, winHeight);

	ofSetColor(255, 0, 0, 255);
	ofDrawBitmapString("Set FrameRate " + ofToString(setFPS), 0, 20);
	ofDrawBitmapString("oF FrameRate " + ofToString(ofGetFrameRate()), 0, 40);
	ofDrawBitmapString("Measured FrameRate " + ofToString(measuredFps), 0, 60);
	ofDrawBitmapString("VSync " + to_string(vsync), 0, 80);
	ofDrawBitmapString("WrapRate " + to_string(wrapRate), 0, 100);
	ofSetColor(255, 255, 255, 255);
	
}
//--------------------------------------------------------------
bool ofApp::loadSettings() {
	ofxXmlSettings settings;
	if (settings.load("Settings.xml")) {
		displayFullscreen = settings.getValue("settings:FullScreen", true);
		wrapRate = settings.getValue("settings:wrapRate", 0.120);
		winWidth = settings.getValue("settings:winWidth", 1920);
		winXPos = settings.getValue("settings:winXPos", 0);
		setFPS = settings.getValue("settings:fps", 120);
		vsync = settings.getValue("settings:vsync", false);
		fullScreen = settings.getValue("settings:fullScreen", false);
		useSubsection = settings.getValue("settings:useSubsection", true);
		fileName = settings.getValue("settings:fileName", "20170115_103555.jpg");
		return true;
	}
	else return false;
}
//--------------------------------------------------------------
bool ofApp::saveSettings() {
	ofxXmlSettings settings;
	settings.setValue("settings:FullScreen", displayFullscreen);
	settings.setValue("settings:wrapRate", wrapRate);
	settings.setValue("settings:winWidth", winWidth);
	settings.setValue("settings:winXPos", winXPos);
	settings.setValue("settings:fps", setFPS);
	settings.setValue("settings:vsync", vsync);
	settings.setValue("settings:fullScreen", fullScreen);
	settings.setValue("settings:useSubsection", useSubsection);
	settings.setValue("settings:fileName", fileName);
	return settings.saveFile("Settings.xml");
}

//--------------------------------------------------------------
void ofApp::exit() {	
	saveSettings();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
		case 'v': vsync = !vsync; ofSetVerticalSync(vsync); break;
		case 'F': setFPS++; ofSetFrameRate(setFPS); break;
		case 'f': setFPS--; ofSetFrameRate(setFPS); break;
		case 'W': wrapRate = wrapRate + 0.01; break;
		case 'w': wrapRate = wrapRate - 0.01; break;
		case 'k': fullScreen = !fullScreen; ofSetFullscreen(fullScreen);
		case 's': saveSettings();
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
	vector< string > fileList = dragInfo.files;
	cout << fileList[0] << endl;
	fileName = fileList[0];
	loaded = currentImage.load(fileName);
}
