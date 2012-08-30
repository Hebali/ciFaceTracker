#include "Expression.h"

Expression::Expression(string description) {
	this->description = description;
}

void Expression::setDescription(string description) {
	this->description = description;
}

string Expression::getDescription() const {
	return description;
}

void Expression::addSample(const cv::Mat& sample) {
	samples.push_back(sample.clone());
}

cv::Mat& Expression::getExample(unsigned int i) {
	return samples[i];
}

unsigned int Expression::size() const {
	return samples.size();
}

void Expression::reset() {
	samples.clear();
}

void Expression::save(string filename) const {
    ofstream tFile;
    /*
    tFile.open( filename );
    tFile << "description" << description << "samples" << "[";
    
    int tCount = size();
    for(int i = 0; i < tCount; i++) {
		tFile << samples[i];
	}
    tFile << "]";
    tFile.close();
    */
    
    /* TODO
	FileStorage fs(ofToDataPath(filename), FileStorage::WRITE);
	fs <<	"description" << description <<
	"samples" << "[";
	for(int i = 0; i < size(); i++) {
		fs << samples[i];
	}
	fs << "]";
    */
}

void Expression::load(string filename) {
    /* TODO
	FileStorage fs(ofToDataPath(filename), FileStorage::READ);
	description = (string) fs["description"];
	FileNode samplesNode = fs["samples"];
	int n = samplesNode.size();
	samples.resize(n);
	for(int i = 0; i < n; i++) {
		samplesNode[i] >> samples[i];
	}
    */
}