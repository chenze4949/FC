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

#import <QuartzCore/QuartzCore.h>

#import "FCApplication_apple.h"
#import "FCViewManager_apple.h"
#import "FlurryAnalytics.h"
#import "TestFlight.h"

UIViewController* s_rootViewController = nil;

UIViewController* FCRootViewController()
{
	return s_rootViewController;
}

FCApplication* plt_FCApplication_Instance();

static FCApplication* s_pInstance = 0;

FCApplication* plt_FCApplication_Instance()
{
	if(!s_pInstance)
	{
		s_pInstance = new FCApplicationProxy;
	}
	return s_pInstance;
}

FCApplicationProxy::FCApplicationProxy()
{
	m_pApp = [[FCApplication_apple alloc] init];
}

FCApplicationProxy::~FCApplicationProxy()
{
	m_pApp = nil;
}

void FCApplicationProxy::ColdBoot( FCApplicationDelegate* pDelegate )
{
	[m_pApp coldBoot];
	FCApplication::ColdBoot(pDelegate);
}

//void FCApplicationProxy::WarmBoot()
//{
//	FC
//}

void FCApplicationProxy::Shutdown()
{
	FC_HALT;
	
}

//void FCApplicationProxy::Update()
//{
//	FC_HALT;
//}

void FCApplicationProxy::Pause()
{
	FCApplication::Pause();
	[m_pApp pause];
}

void FCApplicationProxy::Resume()
{
	FCApplication::Resume();
	[m_pApp resume];
}

void FCApplicationProxy::SetAnalyticsID( std::string ident )
{
	[FlurryAnalytics startSession:[NSString stringWithUTF8String:ident.c_str()]];
//	[m_pApp setAnalyticsID:[NSString stringWithUTF8String:ident.c_str()]];
}

void FCApplicationProxy::SetTestFlightID( std::string ident )
{
	[TestFlight takeOff:[NSString stringWithUTF8String:ident.c_str()]];
//	[m_pApp setTestFlightID:[NSString stringWithUTF8String:ident.c_str()]];
}

void FCApplicationProxy::WillResignActive()
{
	FC_HALT;
	
}

void FCApplicationProxy::DidEnterBackground()
{
	FC_HALT;
	
}

void FCApplicationProxy::WillEnterForeground()
{
	FC_HALT;
	
}

//void FCApplicationProxy::DidBecomeActive()
//{
//	FC_HALT;
//	
//}

void FCApplicationProxy::WillTerminate()
{
	FC_HALT;
	
}

//bool FCApplicationProxy::ShouldAutorotateToInterfaceOrientation( FCInterfaceOrientation orient )
//{
//	return FCApplication::ShouldAutorotateToInterfaceOrientation(orient);
//}

void FCApplicationProxy::ShowExternalLeaderboard()
{
	[m_pApp showGameCenterLeaderboard];
}

void FCApplicationProxy::ShowStatusBar( bool visible )
{
	[m_pApp showStatusBar:visible];
}

void FCApplicationProxy::SetBackgroundColor(FCColor4f &color)
{
	[m_pApp setBackgroundColor:color];
}

FCVector2f FCApplicationProxy::MainViewSize()
{
	CGSize size = [m_pApp mainViewSize];
	
	return FCVector2f( size.width, size.height );
}

void FCApplicationProxy::SetUpdateFrequency(int freq)
{
	[m_pApp setUpdateFrequency:freq];
}

//FCLuaVM* FCApplicationProxy::Lua()
//{
//	FC_HALT;
//	return 0;
//}

void FCApplicationProxy::LaunchExternalURL( std::string url )
{
	NSString* stringURL = [NSString stringWithUTF8String:url.c_str()];
	[m_pApp launchExternalURL:stringURL];
}

void FCApplicationProxy::RegisterExceptionHandler()
{
	[m_pApp registerExceptionHandler];
}

static void uncaughtExceptionHandler(NSException *exception) {
    FC_LOG( "Sending uncaught exception to Flurry" );
    [FlurryAnalytics logError:@"Uncaught" message:@"Crash!" exception:exception];
}


#pragma mark ObjC

@implementation FCApplication_apple

@synthesize displayLink = _displayLink;

-(id)init
{
	self = [super init];
	if (self)
	{
		// plap
	}
	return self;
}

-(void)dealloc
{
	// TODO - remove display link from runloop
}

-(void)registerExceptionHandler
{
	NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
}

-(void)setAnalyticsID:(NSString*)ident
{
}

-(void)setTestFlightID:(NSString*)ident
{
	FC_HALT;
	
}

-(void)coldBoot
{
	FC_ASSERT( s_rootViewController );
	
	_displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
	[_displayLink setFrameInterval:1];
	[_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	
	s_rootViewController.view.backgroundColor = [UIColor blackColor];
	[FCViewManager_apple instance].rootView = s_rootViewController.view;
}

-(void)update
{
	s_pInstance->Update();
}

-(void)pause
{
	[[NSNotificationCenter defaultCenter] postNotificationName:[NSString stringWithUTF8String:kFCNotificationPause.c_str()] object:nil];
}

-(void)resume
{
	[[NSNotificationCenter defaultCenter] postNotificationName:[NSString stringWithUTF8String:kFCNotificationResume.c_str()] object:nil];	
}

-(void)showStatusBar:(bool)visible
{
	if (visible) {
		[[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationNone];
	} else {
		[[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
		s_rootViewController.view.frame = [[UIScreen mainScreen] bounds];
	}
}

-(void)setBackgroundColor:(FCColor4f &)color
{
	s_rootViewController.view.backgroundColor = [UIColor colorWithRed:color.r green:color.g blue:color.b alpha:color.a];
}

-(void)showGameCenterLeaderboard
{
	GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
	
    if (leaderboardController != nil)
    {
        leaderboardController.leaderboardDelegate = self;
        [s_rootViewController presentModalViewController: leaderboardController animated: YES];
    }
}

-(void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController
{
	[s_rootViewController dismissModalViewControllerAnimated:YES];	
	
	// call lua func ?
}

-(void)launchExternalURL:(NSString *)url
{
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
}

-(CGSize)mainViewSize
{
	return s_rootViewController.view.frame.size;
}

-(void)setUpdateFrequency:(int)freq
{
	[_displayLink invalidate];
	_displayLink = nil;
	
	_displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
	[_displayLink setFrameInterval:60 / freq];
	[_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

@end
