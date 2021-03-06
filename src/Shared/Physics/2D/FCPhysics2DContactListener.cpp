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

#include "FCPhysics2DContactListener.h"

FCPhysics2DContactListener::FCPhysics2DContactListener()
{
	
}

FCPhysics2DContactListener::~FCPhysics2DContactListener()
{
	FC_ASSERT(m_subscribers.size() == 0);
}

void FCPhysics2DContactListener::PreSolve( b2Contact* contact, const b2Manifold* oldManifold )
{
	b2WorldManifold worldManifold; contact->GetWorldManifold(&worldManifold);
	
	b2PointState state1[2], state2[2];
	
	b2GetPointStates(state1, state2, oldManifold, contact->GetManifold()); 
	
	if (state2[0] == b2_addState)
	{
		const b2Body* bodyA = contact->GetFixtureA()->GetBody();
		const b2Body* bodyB = contact->GetFixtureB()->GetBody();
		
		b2Vec2 point = worldManifold.points[0];
		
		b2Vec2 vA = bodyA->GetLinearVelocityFromWorldPoint(point); 
		b2Vec2 vB = bodyB->GetLinearVelocityFromWorldPoint(point); 
		
		float32 approachVelocity = b2Dot(vB - vA, worldManifold.normal); 
		
		if (approachVelocity < -0.1f)
		{ 
			FCHandle hActor1 = (FCHandle)bodyA->GetUserData();
			FCHandle hActor2 = (FCHandle)bodyB->GetUserData();
			
			uint64_t key;
			
			if (hActor1 < hActor2) {
				key = ((uint64_t)hActor1) | (((uint64_t)hActor2) << 32);
			} else {
				key = ((uint64_t)hActor2) | (((uint64_t)hActor1) << 32);
			}

			tCollisionMapIter i = m_collisions.find(key);

			if (i == m_collisions.end()) {
				CollisionInfo info;
				info.velocity = approachVelocity;
				info.x = point.x;
				info.y = point.y;
				info.z = 0.0f;
				info.hActor1 = hActor1;
				info.hActor2 = hActor2;
				m_collisions[key] = info;
			} else {
				if (i->second.velocity > approachVelocity) {
					i->second.velocity = approachVelocity;
				}
			}
			
		} 
	}
}

void FCPhysics2DContactListener::Clear()
{
	m_collisions.clear();
}

void FCPhysics2DContactListener::AddSubscriber( tCollisionSubscriber sub )
{
	m_subscribers.insert( sub );
}

void FCPhysics2DContactListener::RemoveSubscriber( tCollisionSubscriber sub )
{
	m_subscribers.erase( sub );
}

void FCPhysics2DContactListener::DispatchToSubscribers()
{
	if (m_collisions.size()) 
	{
		for ( tSubscriberSetIter i = m_subscribers.begin(); i != m_subscribers.end(); ++i ) {
			(*i)(m_collisions);
		}
	}
}

