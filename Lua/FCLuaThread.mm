/*
 Copyright (C) 2011 by Martin Linklater
 
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

#import "FCLuaThread.h"
#import "FCError.h"
#import "FCLuaCommon.h"

extern "C" {
#include "lua.h"
#import "lauxlib.h"
#import "lualib.h"
}

@interface FCLuaThread() {
}
@end

@implementation FCLuaThread
@synthesize state = _state;
@synthesize sleepTimeRemaining = _sleepTimeRemaining;
@synthesize threadId = _threadId;
@synthesize luaState = _luaState;

-(id)initFromState:(lua_State *)state withId:(unsigned int)threadId
{
	self = [super init];
	if (self) {
		_luaState = lua_newthread(state);
		char buffer[32];
		sprintf(&buffer[0], "thread%d", threadId);		
		lua_setfield(state, LUA_REGISTRYINDEX, &buffer[0]);
		_state = kLuaThreadStateNew;
		_sleepTimeRemaining = 0.0;
		_threadId = threadId;
	}
	return self;
}

-(void)dealloc
{
	[super dealloc];
}

-(void)runVoidFunction:(NSString *)function
{
	lua_getglobal(_luaState, [function UTF8String]);
	if (lua_isnil(_luaState, -1)) {
		FC_FATAL1(@"Unknown Lua function", function);
	}
	_state = kLuaThreadStateRunning;
	int ret = lua_resume(_luaState , 0);
	switch (ret) {
		case 0:
			_state = kLuaThreadStateDying;
			break;
		case LUA_YIELD:
			break;
		case LUA_ERRRUN:
			FCLuaCommon_DumpStack(_luaState);
			FC_FATAL(@"LUA_ERRRUN");
			break;
		case LUA_ERRSYNTAX:
			FCLuaCommon_DumpStack(_luaState);
			FC_FATAL(@"LUA_ERRSYNTAX");
			break;
		case LUA_ERRMEM:
			FCLuaCommon_DumpStack(_luaState);
			FC_FATAL(@"LUA_ERRMEM");
			break;
		case LUA_ERRERR:
			FCLuaCommon_DumpStack(_luaState);
			FC_FATAL(@"LUA_ERRERR");
			break;
		default:
			break;
	}
}

-(void)update:(float)dt
{
	switch (self.state) {
		case kLuaThreadStateNew:
			break;
		case kLuaThreadStateRunning:
			{
				int ret = lua_resume(_luaState , 0);
				switch (ret) {
					case 0:
						_state = kLuaThreadStateDying;
						break;
					case LUA_YIELD:
						break;
					case LUA_ERRRUN:
						FCLuaCommon_DumpStack(_luaState);
						FC_FATAL(@"LUA_ERRRUN");
						break;
					case LUA_ERRSYNTAX:
						FCLuaCommon_DumpStack(_luaState);
						FC_FATAL(@"LUA_ERRSYNTAX");
						break;
					case LUA_ERRMEM:
						FCLuaCommon_DumpStack(_luaState);
						FC_FATAL(@"LUA_ERRMEM");
						break;
					case LUA_ERRERR:
						FCLuaCommon_DumpStack(_luaState);
						FC_FATAL(@"LUA_ERRERR");
						break;
					default:
						FC_FATAL(@"default fallthrough");
						break;
				}
			}
			break;
		case kLuaThreadStateSleeping:
			{
				_sleepTimeRemaining -= dt;
				if (_sleepTimeRemaining <= 0.0) {
					_state = kLuaThreadStateRunning;
				}
			}
			break;
		case kLuaThreadStateDying:
			_state = kLuaThreadStateDead;
			lua_pushnil(_luaState);
			char buffer[32];
			sprintf(&buffer[0], "thread%d", _threadId);		
			lua_setfield(_luaState, LUA_REGISTRYINDEX, &buffer[0]);			
			break;
		case kLuaThreadStateDead:
			break;			
	}
}

-(void)die
{
	_state = kLuaThreadStateDying;
}

-(void)pause:(float)seconds
{
	_sleepTimeRemaining = (float)seconds;
	_state = kLuaThreadStateSleeping;
}

-(NSString*)description
{
	switch (_state) {
		case kLuaThreadStateDead:
			return @"Dead";
			break;
		case kLuaThreadStateDying:
			return @"Dying";
			break;
		case kLuaThreadStateNew:
			return @"New";
			break;
		case kLuaThreadStateRunning:
			return @"Running";
			break;
		case kLuaThreadStateSleeping:
			return @"Sleeping";
			break;
			
		default:
			break;
	}
}

@end