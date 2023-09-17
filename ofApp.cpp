#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(0.8);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->location_list.clear();

	ofColor color;
	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	for (int i = 0; i < 3; i++) {

		for (int x = -600; x <= 600; x += 4) {

			auto base_y = ofMap(ofNoise(noise_seed.x, x * 0.001 + (ofGetFrameNum() + i * 10000) * 0.002), 0, 1, -400, 400);
			auto base_z = ofMap(ofNoise(noise_seed.y, x * 0.001 + (ofGetFrameNum() + i * 10000) * 0.002), 0, 1, -200, 200);

			auto y = base_y + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -50, 50);
			auto z = base_z + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -50, 50);
			this->location_list.push_back(glm::vec3(x, y, z));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (auto& location : this->location_list) {

		ofPushMatrix();
		ofTranslate(location);

		ofRotateZ(ofRandom(360));
		ofRotateY(ofRandom(360));
		ofRotateZ(ofRandom(360));

		ofSetColor(0);
		ofFill();
		ofDrawBox(15);

		ofSetColor(255);
		ofNoFill();
		ofDrawBox(15);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}