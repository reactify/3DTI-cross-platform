//
//  StereoSpread.hpp
//  example-ios
//
//  Created by Ragnar Hrafnkelsson on 01/11/2015.
//  Copyright © 2015 Reactify. All rights reserved.
//

#ifndef StereoSpread_h
#define StereoSpread_h

#include <stdio.h>

class StereoSpread
{
public:
	StereoSpread();
	
	~StereoSpread();
	
	void setWidth(float w);
	
	void process(float **inBuffer, float **outBuffers, const int bufferSize);

private:
	
	float width;
};

#endif /* StereoSpread_h */
