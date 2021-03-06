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

#ifndef _FCGLShaderProgramWireframe_h
#define _FCGLShaderProgramWireframe_h

#include "Shared/Graphics/FCGraphics.h"

#include "GLES/FCGLShaderProgram.h"

class FCGLShaderProgramWireframe : public FCGLShaderProgram
{
public:
	FCGLShaderProgramWireframe( FCGLShaderRef vertexShader, FCGLShaderRef fragmentShader )
	: FCGLShaderProgram( vertexShader, fragmentShader )
	{
		m_stride = 12;
		m_diffuseColorUniform = m_uniforms[ "diffuse_color" ];
		m_positionAttribute = m_attributes[ "position" ];
	}
	
	virtual ~FCGLShaderProgramWireframe()
	{
		
	}

	void BindUniformsWithMesh( FCGLMesh* mesh )
	{
		FCColor4f diffuseColor = mesh->DiffuseColor();
		FCglUniform4fv( m_diffuseColorUniform->Location(), m_diffuseColorUniform->Num(), (GLfloat*)&diffuseColor );
	}
	
	void BindAttributes()
	{
		FCglVertexAttribPointer( m_positionAttribute->Location(), 3, GL_FLOAT, GL_FALSE, m_stride, (void*)0 );
		FCglEnableVertexAttribArray( m_positionAttribute->Location() );
	}
	
	FCGLShaderUniformRef	m_diffuseColorUniform;
	FCGLShaderAttributeRef	m_positionAttribute;
};


#endif
