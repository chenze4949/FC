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

#ifndef CR1_FCPhysics2D_h
#define CR1_FCPhysics2D_h

#include <map>

#include <Box2D/Box2D.h>

#include "Shared/Core/FCCore.h"
#include "FCPhysics2DBody.h"
#include "FCPhysics2DContactListener.h"
#include "FCPhysics2DJoint.h"


class FCPhysics2D : public FCBase {
public:	
	FCPhysics2D();
	virtual ~FCPhysics2D();
	
	void Init();
	
//	b2World*	World(){ return m_pWorld; }
//	void		SetWorld( b2World* pWorld ){ m_pWorld = pWorld; }
//
//	b2Vec2		Gravity(){ return m_gravity; }
//	void		SetGravity( const b2Vec2& gravity ){ m_gravity = gravity; }

	void	Update( float realTime, float gameTime );
	void	PrepareForDealloc();
	
	FCPhysics2DBodyPtr	CreateBody( FCPhysics2DBodyDefPtr def, std::string name, FCHandle actorHandle );
	void				DestroyBody( FCPhysics2DBodyPtr body );
	FCPhysics2DBodyPtr	BodyWithName( std::string name );
	
	FCHandle	CreateJoint( FCPhysics2DJointCreateDefPtr def );
	void		SetRevoluteJointMotor( FCHandle joint, bool enabled, float torque, float speed );
	void		SetRevoluteJointLimits( FCHandle joint, bool enable, float min, float max );
	
	void		SetPrismaticJointMotor( FCHandle joint, bool enable, float force, float speed );
	void		SetPrismaticJointLimits( FCHandle joint, bool enable, float min, float max );
	
	FCPhysics2DContactListener* ContactListener();
	
private:
	b2World*					m_pWorld;
	b2Vec2						m_gravity;
	FCPhysics2DJointMapByHandle	m_joints;
	FCPhysics2DBodyPtrByHandle	m_bodies;
	FCPhysics2DBodyPtrMapByName	m_bodiesByName;
	FCPhysics2DContactListener*	m_contactListener;
};

typedef std::shared_ptr<FCPhysics2D> FCPhysics2DPtr;

#endif