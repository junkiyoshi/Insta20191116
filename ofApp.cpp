#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	ofPixels pixels;
	ofLoadImage(pixels, "D:\\lena.png");
	int span = 2;
	for (int x = 0; x < pixels.getWidth(); x += span) {

		for (int y = 0; y < pixels.getHeight(); y += span) {

			auto vertex = glm::vec2(x, pixels.getHeight() - y) - glm::vec2(pixels.getWidth() * 0.5, pixels.getHeight() * 0.5);
			auto color = pixels.getColor(x, y);

			this->mesh.addVertex(glm::vec3(vertex, 0));
			this->mesh.addColor(color);
		}
	}

	int cols = pixels.getWidth() / span;
	int rows = pixels.getHeight() / span;

	for (int col = 1; col < cols; col++) {

		for (int row = 1; row < rows; row++) {

			this->mesh.addIndex(col + row * cols); 
			this->mesh.addIndex((col - 1) + (row - 1) * cols);
			this->mesh.addIndex((col - 1) + row * cols);

			this->mesh.addIndex(col + row * cols);
			this->mesh.addIndex((col - 1) + (row - 1) * cols);
			this->mesh.addIndex(col + (row - 1) * cols);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh = this->mesh;

	for (auto& vertex : this->draw_mesh.getVertices()) {

		auto angle_y = ofMap(ofNoise(vertex.y * 0.005 + ofGetFrameNum() * 0.01), 0, 1, -PI * 2, PI * 2);
		auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

		vertex = glm::vec4(vertex, 0) * rotation_y;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->draw_mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}