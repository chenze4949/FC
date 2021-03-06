/*
 Copyright (C) 2011-2012 by Martin Linklater
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

//#import <Foundation/Foundation.h>

#ifndef FCMatrix_h
#define FCMatrix_h

#include <math.h>
#include "FCVector.h"

class FCMatrix4f {
public:
	FCMatrix4f(){}
	FCMatrix4f( const FCMatrix4f& mat ) {
		e[0] = mat.e[0]; e[1] = mat.e[1]; e[2] = mat.e[2]; e[3] = mat.e[3];
		e[4] = mat.e[4]; e[5] = mat.e[5]; e[6] = mat.e[6]; e[7] = mat.e[7];
		e[8] = mat.e[8]; e[9] = mat.e[9]; e[10] = mat.e[10]; e[11] = mat.e[11];
		e[12] = mat.e[12]; e[13] = mat.e[13]; e[14] = mat.e[14]; e[15] = mat.e[15];
	}

	static FCMatrix4f Identity( void ) {
		FCMatrix4f mat;
		mat.e[0] = mat.e[5] = mat.e[10] = mat.e[15] = 1.0f;
		mat.e[1] = mat.e[2] = mat.e[3] = mat.e[4] = mat.e[6] = mat.e[7] = mat.e[8] = mat.e[9] = mat.e[11] = mat.e[12] = mat.e[13] = mat.e[14] = 0.0f;
		return mat;
	}
	
	FCMatrix4f Transpose( void ) {
		FCMatrix4f ret;
		ret.e[0] = e[0]; ret.e[1] = e[4]; ret.e[2] = e[8]; ret.e[3] = e[12];
		ret.e[4] = e[1]; ret.e[5] = e[5]; ret.e[6] = e[9]; ret.e[7] = e[13];
		ret.e[8] = e[2]; ret.e[9] = e[6]; ret.e[10] = e[10]; ret.e[11] = e[14];
		ret.e[12] = e[3]; ret.e[13] = e[7]; ret.e[14] = e[11]; ret.e[15] = e[15];
		return ret;
	}
	
	static FCMatrix4f Frustum( float left, float right, float bottom, float top, float near, float far ) {
		FCMatrix4f mat;
		
		float a = 2 * near / ( right - left );
		float b = 2 * near / ( top - bottom );
		float c = ( right + left ) / ( right - left );
		float d = ( top + bottom ) / ( top - bottom );
		float E = -( far + near ) / ( far - near );
		float f = -2 * far * near / ( far - near );
		
		mat.e[0] = a; mat.e[1] = mat.e[2] = mat.e[3] = 0.0f;
		mat.e[4] = 0; mat.e[5] = b; mat.e[6] = mat.e[7] = 0;
		mat.e[8] = c; mat.e[9] = d; mat.e[10] = E; mat.e[11] = -1;
		mat.e[12] = 0; mat.e[13] = 0; mat.e[14] = f; mat.e[15] = 1;

		return mat;
	}

	static FCMatrix4f Orthographic( float width, float height, float near, float far ) {
		FCMatrix4f mat;
		
		mat.e[0] = 2.0f / width;
		mat.e[5] = 2.0f / height;
		mat.e[10] = 2.0f / (far - near);
		mat.e[15] = 1.0f;
		
		mat.e[1] = mat.e[2] = mat.e[3] = mat.e[4] = mat.e[6] = mat.e[7] = mat.e[8] = mat.e[9] = mat.e[11] = mat.e[12] = mat.e[13] = mat.e[14] = 0.0f;
		
		return mat;
	}

	static FCMatrix4f Translate( float x, float y, float z ) {
		FCMatrix4f mat;
		mat.e[0] = mat.e[5] = mat.e[10] = mat.e[15] = 1.0f;
		mat.e[1] = mat.e[2] = mat.e[3] = mat.e[4] = mat.e[6] = mat.e[7] = mat.e[8] = mat.e[9] = mat.e[11] = 0.0f;
		mat.e[12] = x;
		mat.e[13] = y;
		mat.e[14] = z;
		return mat;
	}
	
	FCMatrix4f operator*( FCMatrix4f &mat ) const
	{
		FCMatrix4f out;
		out.e[0] = (e[0] * mat.e[0]) + (e[1] * mat.e[4]) + (e[2] * mat.e[8]) + (e[3] * mat.e[12]);
		out.e[1] = (e[0] * mat.e[1]) + (e[1] * mat.e[5]) + (e[2] * mat.e[9]) + (e[3] * mat.e[13]);
		out.e[2] = (e[0] * mat.e[2]) + (e[1] * mat.e[6]) + (e[2] * mat.e[10]) + (e[3] * mat.e[14]);
		out.e[3] = (e[0] * mat.e[3]) + (e[1] * mat.e[7]) + (e[2] * mat.e[11]) + (e[3] * mat.e[15]);
		
		out.e[4] = (e[4] * mat.e[0]) + (e[5] * mat.e[4]) + (e[6] * mat.e[8]) + (e[7] * mat.e[12]);
		out.e[5] = (e[4] * mat.e[1]) + (e[5] * mat.e[5]) + (e[6] * mat.e[9]) + (e[7] * mat.e[13]);
		out.e[6] = (e[4] * mat.e[2]) + (e[5] * mat.e[6]) + (e[6] * mat.e[10]) + (e[7] * mat.e[14]);
		out.e[7] = (e[4] * mat.e[3]) + (e[5] * mat.e[7]) + (e[6] * mat.e[11]) + (e[7] * mat.e[15]);
		
		out.e[8] = (e[8] * mat.e[0]) + (e[9] * mat.e[4]) + (e[10] * mat.e[8]) + (e[11] * mat.e[12]);
		out.e[9] = (e[8] * mat.e[1]) + (e[9] * mat.e[5]) + (e[10] * mat.e[9]) + (e[11] * mat.e[13]);
		out.e[10] = (e[8] * mat.e[2]) + (e[9] * mat.e[6]) + (e[10] * mat.e[10]) + (e[11] * mat.e[14]);
		out.e[11] = (e[8] * mat.e[3]) + (e[9] * mat.e[7]) + (e[10] * mat.e[11]) + (e[11] * mat.e[15]);

		out.e[12] = (e[12] * mat.e[0]) + (e[13] * mat.e[4]) + (e[14] * mat.e[8]) + (e[15] * mat.e[12]);
		out.e[13] = (e[12] * mat.e[1]) + (e[13] * mat.e[5]) + (e[14] * mat.e[9]) + (e[15] * mat.e[13]);
		out.e[14] = (e[12] * mat.e[2]) + (e[13] * mat.e[6]) + (e[14] * mat.e[10]) + (e[15] * mat.e[14]);
		out.e[15] = (e[12] * mat.e[3]) + (e[13] * mat.e[7]) + (e[14] * mat.e[11]) + (e[15] * mat.e[15]);
		return out;
	}
	
	static FCMatrix4f Rotate( float angle, FCVector3f axis )
	{
		float s = (float)sin(angle);
		float c = (float)cos(angle);
		
		FCMatrix4f mat = FCMatrix4f::Identity();
		
		mat.e[0] = c + (1 - c) * axis.x * axis.x;
		mat.e[1] = (1 - c) * axis.x * axis.y - axis.z * s;
		mat.e[2] = (1 - c) * axis.x * axis.z + axis.y * s;
		mat.e[4] = (1 - c) * axis.x * axis.y + axis.z * s;
		mat.e[5] = c + (1 - c) * axis.y * axis.y;
		mat.e[6] = (1 - c) * axis.y * axis.z - axis.x * s;
		mat.e[8] = (1 - c) * axis.x * axis.z - axis.y * s;
		mat.e[9] = (1 - c) * axis.y * axis.z + axis.x * s;
		mat.e[10] = c + (1 - c) * axis.z * axis.z;
		
		return mat;
	}
			
	float	e[16];
};
 
static FCVector3f operator *( const FCVector3f& vec, const FCMatrix4f& mat )
{
	FCVector3f ret;
	ret.x = vec.x * mat.e[0] + vec.y * mat.e[1] + vec.z * mat.e[2];
	ret.y = vec.x * mat.e[4] + vec.y * mat.e[5] + vec.z * mat.e[6];
	ret.z = vec.x * mat.e[8] + vec.y * mat.e[9] + vec.z * mat.e[10];
	return ret;
}
	
#endif // FCMatrix_h
