/*
 ciFaceTracker provides an interface to Jason Saragih's FaceTracker library.
 
 getImagePoint()/getImageMesh() are in image space. This means that all the
 points will line up with the pixel coordinates of the image you fed into
 ciFaceTracker.
 
 getObjectPoint()/getObjectMesh() are in 3d object space. This is a product of
 the mean mesh with only the expression applied. There is no rotation or
 translation applied to the object space.
 
 getMeanObjectPoint()/getMeanObjectMesh() are also in 3d object space. However,
 there is no expression applied to the mesh.
 */

#pragma once

#include <sstream>

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/TriMesh.h"

#include "CinderOpenCv.h"

#include "FTracker.h"
#include "ExpressionClassifier.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace FACETRACKER;

class ciFaceTracker {
public:
	ciFaceTracker();
	void setup();
	virtual bool update(cv::Mat image);
	void draw(bool drawLabels = false) const;
	void reset();
	
	int size() const;
	bool getFound() const;
	int getAge() const;
	virtual bool getVisibility(int i) const;
	
	vector<Vec3f> getImagePoints() const;
	vector<Vec3f> getObjectPoints() const;
	vector<Vec3f> getMeanObjectPoints() const;
	
	virtual Vec3f getImagePoint(int i) const;
	virtual Vec3f getObjectPoint(int i) const;
	virtual Vec3f getMeanObjectPoint(int i) const;
	
	TriMesh getImageMesh() const;
	TriMesh getObjectMesh() const;
	TriMesh getMeanObjectMesh() const;
	TriMesh getMesh(vector<Vec3f> points) const;
	
	virtual const cv::Mat& getObjectPointsMat() const;
	
	virtual Vec2f getPosition() const;
	virtual float getScale() const;
	virtual Vec3f getOrientation() const;
	Matrix44f getRotationMatrix() const;
	
	enum Direction {
		FACING_FORWARD,
		FACING_LEFT, FACING_RIGHT,
		FACING_UNKNOWN
	};
	Direction getDirection() const;
	
	enum Feature {
		LEFT_EYEBROW, RIGHT_EYEBROW,
		LEFT_EYE, RIGHT_EYE,
		LEFT_JAW, RIGHT_JAW, JAW,
		OUTER_MOUTH, INNER_MOUTH,
		NOSE_BRIDGE, NOSE_BASE,
		FACE_OUTLINE, ALL_FEATURES
	};
	Path2d getImageFeature(Feature feature) const;
	Path2d getObjectFeature(Feature feature) const;
	Path2d getMeanObjectFeature(Feature feature) const;
	
	enum Gesture {
		MOUTH_WIDTH, MOUTH_HEIGHT,
		LEFT_EYEBROW_HEIGHT, RIGHT_EYEBROW_HEIGHT,
		LEFT_EYE_OPENNESS, RIGHT_EYE_OPENNESS,
		JAW_OPENNESS,
		NOSTRIL_FLARE
	};
	float getGesture(Gesture gesture) const;
	
	void setRescale(float rescale);
	void setIterations(int iterations);
	void setClamp(float clamp);
	void setTolerance(float tolerance);
	void setAttempts(int attempts);
	void setUseInvisible(bool useInvisible);
	
protected:
	void updateObjectPoints();
	void addTriangleIndices(TriMesh& mesh) const;
	static vector<int> getFeatureIndices(Feature feature);
	Path2d getFeature(Feature feature, vector<Vec3f> points) const;
	
	bool failed;
	int age;
	int currentView;
	
	bool fcheck;
	double rescale;
	int frameSkip;
	
	vector<int> wSize1, wSize2;
	int iterations;
	int attempts;
	double clamp, tolerance;
	bool useInvisible;
	
	FACETRACKER::Tracker tracker;
	cv::Mat tri, con;
	
	cv::Mat im, gray;
	cv::Mat objectPoints;
};
