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
    cv::FileStorage fs( filename, cv::FileStorage::WRITE);
	fs <<	"description" << description <<
	"samples" << "[";
	for(int i = 0; i < size(); i++) {
		fs << samples[i];
	}
	fs << "]";
}

void Expression::load(string filename) {
	cv::FileStorage fs( filename, cv::FileStorage::READ);
	description = (string) fs["description"];
	cv::FileNode samplesNode = fs["samples"];
	int n = samplesNode.size();
	samples.resize(n);
	for(int i = 0; i < n; i++) {
		samplesNode[i] >> samples[i];
	}
}