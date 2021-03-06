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

#if defined( FC_ADS )

#import "FCAdBannerView_apple.h"
#import "FCViewManager_apple.h"

#include "Shared/FCPlatformInterface.h"
#include "FCApplication_apple.h"

@implementation FCAdBannerView_apple

- (id)initWithFrame:(CGRect)frame key:(NSString*)key
{
    self = [super initWithFrame:frame];
    if (self) {
		_adWhirlKey = key;
		_adWhirlView = [AdWhirlView requestAdWhirlViewWithDelegate:self];
		[self addSubview:_adWhirlView];

		fc_FCLua_SetGlobalNumber("AdBannerHeight", 0);
    }
    return self;
}

-(void)dealloc
{
	fc_FCLua_SetGlobalNumber("AdBannerHeight", 0);
	_adWhirlView .delegate = nil;
}

- (NSString *)adWhirlApplicationKey 
{
	return _adWhirlKey;
}

- (UIViewController *)viewControllerForPresentingModalView 
{
	return _viewController;
}

- (void)adWhirlDidReceiveAd:(AdWhirlView *)adWhirlView 
{
	[self bringSubviewToFront:_adWhirlView];
	
	[UIView beginAnimations:@"blah" context:nil];
	
	[UIView setAnimationDuration:0.7];
	
	CGSize adSize = [_adWhirlView actualAdSize];
	CGRect newFrame = _adWhirlView.frame;
	
	newFrame.size = adSize;
    newFrame.origin.x = (FCRootViewController().view.bounds.size.width - adSize.width)/ 2;
	
	_adWhirlView.frame = newFrame;
	self.frame = newFrame;
	
	[UIView commitAnimations];
	fc_FCLua_SetGlobalNumber("AdBannerHeight", adSize.height);
}

@end

#endif // FC_ADS
