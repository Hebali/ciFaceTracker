#pragma once

#include <iostream>
#include <sstream>
#include <iterator>
#include <boost/filesystem.hpp>

#include "Expression.h"

#include "ciFaceTracker.h"
class ciFaceTracker;

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace boost::filesystem;

class ExpressionClassifier {
public:
	ExpressionClassifier();
	void            save(string directory) const;
	void            load(string directory);
	unsigned int    classify(const ciFaceTracker& tracker);
	unsigned int    getPrimaryExpression() const;
	double          getProbability(unsigned int i) const;
	string          getDescription(unsigned int i) const;
	Expression&     getExpression(unsigned int i);
	void            setSigma(double sigma);
	double          getSigma() const;
	unsigned int    size() const;
	void            addExpression(string description = "");
	void            addExpression(Expression& expression);
	void            addSample(const ciFaceTracker& tracker);
	void            reset();
protected:
	vector<Expression> expressions;
	vector<double> probability;
	float sigma;
};
