#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofImage currentImage;
		ofFbo canvasFBO, outputFBO;

		float wrapAmount;
		float wrapRate = 0.12;
		int setFPS = 120;
		float accumulateStartTime;
		int drawCount;
		float accumulatedTime = 0;
		float timeBetweenDraws;
		float lastDrawTime;
		float measuredFps;
		float ofFps;
		bool vsync = false;
		bool fullScreen = false;

		bool useSubsection = false;

		bool showGUI = true;
		bool initialised = false;
		bool loaded = false;
		bool displayFullscreen = false;
		int winXPos = 1920;
		int winYPos = 0;
		int winWidth = 9600;
		int winHeight= 1080;
		int fboWidth = 9600;
		int fboHeight = 1080;
		string fileName = "";

		bool loadSettings();
		bool saveSettings();

		void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
