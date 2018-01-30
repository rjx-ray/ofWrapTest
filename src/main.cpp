#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {


	ofGLFWWindowSettings settings;

	settings.width = 1920;
	settings.height = 500;
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	shared_ptr<ofApp> mainApp(new ofApp());

	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
