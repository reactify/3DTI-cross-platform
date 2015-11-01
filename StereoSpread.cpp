//
//  StereoSpread.cpp
//  example-ios
//
//  Created by Ragnar Hrafnkelsson on 01/11/2015.
//  Copyright © 2015 Reactify. All rights reserved.
//

#include "StereoSpread.h"

StereoSpread::StereoSpread() : width(1.f)
{
	
}

StereoSpread::~StereoSpread()
{
	
}

void StereoSpread::setWidth(float w)
{
	if (w < 0.f) w = 0.f; if (w > 1.f) w = 1.f;
	width = w;
}

// http://musicdsp.org/showArchiveComment.php?ArchiveID=256
void StereoSpread::process(float **inBuffers, float **outBuffers, const int bufferSize)
{
	// calculate scale coefficient
	float coef_S = width * 0.5f;
	
	float* inLeft = inBuffers[0];
	float* inRight = inBuffers[1];
	float* outLeft = outBuffers[0];
	float* outRight = outBuffers[1];
	
	for (int i = 0; i < bufferSize; i++)
	{
		float m = (inLeft[i] + inRight[i]) * 0.5f;
		float s = (inRight[i] - inLeft[i]) * coef_S;
		
		outLeft[i] = m - s;
		outRight[i] = m + s;
	}
}

