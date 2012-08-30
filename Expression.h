#pragma once

#include <iostream>
#include <fstream>

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/TriMesh.h"

#include "CinderOpenCv.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Expression {
public:
	Expression(string description = "");
    
	void            setDescription(string description);
	string          getDescription() const;
    
	void            addSample(const cv::Mat& sample);
	cv::Mat&        getExample(unsigned int i);
	unsigned int    size() const;
	void            reset();
	void            save(string filename) const;
	void            load(string filename);
    
protected:
	string description;
	vector<cv::Mat> samples;
};