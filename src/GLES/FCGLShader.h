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

#ifndef CR1_FCGLShader_h
#define CR1_FCGLShader_h

#include "Shared/Graphics/FCGraphics.h"

#include <string>
#include <map>

#include "FCGL.h"
#include "Shared/Graphics/FCGraphicsTypes.h"

class FCGLShader
{
public:
	FCGLShader( eFCShaderType type, std::string source );
	virtual ~FCGLShader();

	void SetHandle( GLuint handle ){ m_glHandle = handle; }
	GLuint	Handle(){ return m_glHandle; }

private:
	GLuint	m_glHandle;
};

typedef std::shared_ptr<FCGLShader>	FCGLShaderRef;

typedef std::map<std::string, FCGLShaderRef>	FCGLShaderRefMapByString;
typedef FCGLShaderRefMapByString::iterator		FCGLShaderRefMapByStringIter;

#endif
