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

#ifndef _FCPhysics_h
#define _FCPhysics_h

#include "Shared/Core/FCCore.h"

#include "Shared/Physics/2D/FCPhysics2D.h"
#include "Shared/Physics/FCPhysicsMaterial.h"

class FCPhysics : public FCBase {
public:
	FCPhysics();
	virtual ~FCPhysics();
	
	static FCPhysics* Instance();
	
	void Create2DSystem();
	void SetMaterial( FCPhysicsMaterialRef material );
	FCPhysicsMaterialRefMapByString& GetMaterials();
	void Update( float realTime, float gameTime );
	void Reset();
	FCPhysics2DRef TwoD(){ return m_2D; }
private:
	FCPhysics2DRef	m_2D;
	FCPhysicsMaterialRefMapByString m_materials;
};

#endif

