//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//

#import "NSView.h"

@class NSImage, NSImageView, NSLayoutConstraint, NSMutableArray, NSString, NSTextField;

@interface IOBluetoothPasskeyDisplay_tmp : NSView
{
    NSImageView *mReturnImageView;	// 152 = 0x98
    NSImage *mReturnImage;	// 160 = 0xa0
    NSImage *mReturnHighlightImage;	// 168 = 0xa8
    NSImageView *mBackgroundImage;	// 176 = 0xb0
    BOOL usePasskeyNotifications;	// 184 = 0xb8
    NSString *passkey;	// 192 = 0xc0
    NSTextField *mPasskeyString;	// 200 = 0xc8
    NSMutableArray *mPasskeyCharacters;	// 208 = 0xd0
    unsigned long long mPasskeyIndex;	// 216 = 0xd8
    NSLayoutConstraint *backgroundImageConstraint;	// 224 = 0xe0
    NSView *centeredView;	// 232 = 0xe8
}

+ (id)sharedDisplayView;	// IMP=0x0000000000017204
@property NSView *centeredView; // @synthesize centeredView;
@property NSLayoutConstraint *backgroundImageConstraint; // @synthesize backgroundImageConstraint;
@property(retain) NSImage *returnHighlightImage; // @synthesize returnHighlightImage=mReturnHighlightImage;
@property(retain) NSImage *returnImage; // @synthesize returnImage=mReturnImage;
@property(copy) NSString *passkey; // @synthesize passkey;
@property BOOL usePasskeyNotificaitons; // @synthesize usePasskeyNotificaitons=usePasskeyNotifications;
- (void)setPasskeyString:(id)arg1;	// IMP=0x0000000000017d84
- (void)setupUIForSSPDevice:(id)arg1;	// IMP=0x0000000000017d3c
- (void)setupUIForDevice:(id)arg1;	// IMP=0x0000000000017cf7
- (void)setPasskeyIndicatorEnabled:(BOOL)arg1;	// IMP=0x0000000000017cf1
- (void)resetAll;	// IMP=0x0000000000017ceb
- (void)setPasskey:(id)arg1 forDevice:(id)arg2 usingSSP:(BOOL)arg3;	// IMP=0x0000000000017aa9
- (void)resetPasskeyIndicator;	// IMP=0x0000000000017963
- (void)retreatPasskeyIndicator;	// IMP=0x0000000000017875
- (void)advancePasskeyIndicator;	// IMP=0x0000000000017758
- (void)setReturnType:(int)arg1;	// IMP=0x000000000001744a
- (void)awakeFromNib;	// IMP=0x0000000000017321
- (void)dealloc;	// IMP=0x00000000000172d7
- (void)_displayPasskey;	// IMP=0x0000000000016e2a
- (void)_displayPasskeyIndicator;	// IMP=0x0000000000016ccb
- (id)fauxUIElementValue:(id)arg1;	// IMP=0x0000000000001fe4
- (struct CGSize)fauxUIElementSize:(id)arg1;	// IMP=0x0000000000001f7f
- (struct CGPoint)fauxUIElementPosition:(id)arg1;	// IMP=0x0000000000001ee4
- (void)fauxUIElement:(id)arg1 setFocus:(id)arg2;	// IMP=0x0000000000001ede
- (BOOL)isFauxUIElementFocusable:(id)arg1;	// IMP=0x0000000000001ed6
- (id)accessibilityHitTest:(struct CGPoint)arg1;	// IMP=0x0000000000001dae
- (id)accessibilityAttributeValue:(id)arg1;	// IMP=0x0000000000001c76
- (BOOL)accessibilityIsIgnored;	// IMP=0x0000000000001c6e

@end

