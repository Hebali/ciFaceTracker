# ciFaceTracker 

ciFaceTracker is a port of [Kyle McDonald](https://github.com/kylemcdonald)'s ofxFaceTracker, which is based on Jason Saragih's FaceTracker library.

See [ofxFaceTracer on GitHub](https://github.com/kylemcdonald/ofxFaceTracker)

The model file paths ("face2.tracker", etc) are pulled from the package contents using:

path tBasePath = path( ci::app::AppBasic::getResourcePath() );

So, in Xcode, you can drop the model folder into Resources and you don't have to deal with "Resources.h"
I haven't tested this on Windows and suspect it won't work - making this a temporary hack. 

TODO:
- Test Expression and ExpressionClassifier file loading and saving. Should be implemented now, haven't had time to test yet. 