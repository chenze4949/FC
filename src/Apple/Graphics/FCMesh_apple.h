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

#if defined(FC_GRAPHICS)

#import <Foundation/Foundation.h>

#include "Shared/Graphics/FCMesh.h"

@class FCMesh_apple;

//

class FCMeshProxy : public FCMesh
{
public:
	FCMesh_apple*	mesh;
};

//

@class FCShaderProgram_apple;
@class FCModel_apple;

@interface FCMesh_apple : NSObject 
{	
	__weak FCModel_apple*	_parentModel;
	unsigned int			_vertexBufferStride;
	unsigned int			_numVertices;
	unsigned int			_numTriangles;
	unsigned int			_numEdges;
	FCShaderProgram_apple*	_shaderProgram;
	unsigned int			_sizeVertexBuffer;
	void*					_pVertexBuffer;	
	unsigned int			_sizeIndexBuffer;
	unsigned short*			_pIndexBuffer;
	GLuint					_vertexBufferHandle;
	GLuint					_indexBufferHandle;	
	BOOL					_fixedUp;
	GLenum					_primitiveType;

	FCColor4f				_diffuseColor;
	FCColor4f				_specularColor;
}
@property(nonatomic, weak) FCModel_apple* parentModel;
@property(nonatomic, readonly) unsigned int vertexBufferStride;
@property(nonatomic) unsigned int numVertices;
@property(nonatomic) unsigned int numTriangles;
@property(nonatomic) unsigned int numEdges;
@property(nonatomic) unsigned int sizeVertexBuffer;
@property(nonatomic, readonly) void* pVertexBuffer;
@property(nonatomic) unsigned int sizeIndexBuffer;
@property(nonatomic, readonly) unsigned short* pIndexBuffer;
@property(nonatomic, strong) FCShaderProgram_apple* shaderProgram;
@property(nonatomic) GLuint vertexBufferHandle;
@property(nonatomic) GLuint indexBufferHandle;
@property(nonatomic, readonly) BOOL fixedUp;
@property(nonatomic, readonly) GLenum primitiveType;

@property(nonatomic) FCColor4f diffuseColor;
@property(nonatomic) FCColor4f specularColor;

-(id)initWithShaderName:(NSString*)shaderName primitiveType:(GLenum)primitiveType;

-(void)render;
-(unsigned short*)pIndexBufferAtIndex:(unsigned short)index;
@end

#endif // defined(FC_GRAPHICS)