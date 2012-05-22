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

#import <Foundation/Foundation.h>

@interface FCConnect_apple : NSObject <NSNetServiceDelegate, NSStreamDelegate> {
	uint16_t		m_port;
	uint32_t		m_protocolFamily;
	CFSocketRef		m_socketRef;
	NSNetService*	m_netService;
	NSString*		m_bonjourIdentifier;
	NSMutableArray*	m_sendQueue;
	
	BOOL			_connected;
	NSInputStream*	_inputStream;
	NSOutputStream*	_outputStream;
}
@property(nonatomic) BOOL connected;
@property(nonatomic, strong) NSInputStream* inputStream;
@property(nonatomic, strong) NSOutputStream* outputStream;

+(FCConnect_apple*)instance;

-(BOOL)start;
-(BOOL)enableWithName:(NSString*)name;
-(void)stop;

//-(void)setInputStream:(NSInputStream*)iStream andOutputStream:(NSOutputStream*)oStream;
-(void)sendNextString;
-(void)sendString:(NSString*)string;

@end