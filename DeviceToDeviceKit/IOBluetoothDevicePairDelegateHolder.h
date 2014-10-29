//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//

#import "NSObject.h"

#import "IOBluetoothDevicePairDelegate.h"

@interface IOBluetoothDevicePairDelegateHolder : NSObject <IOBluetoothDevicePairDelegate>
{
    id <D2DPairingDelegate> _delegate;	// 8 = 0x8
}

+ (id)withDelegate:(id)arg1;	// IMP=0x0000000000007f08
@property __weak id <D2DPairingDelegate> delegate; // @synthesize delegate=_delegate;
- (void)deviceSimplePairingComplete:(id)arg1 status:(unsigned char)arg2;	// IMP=0x00000000000083a9
- (void)devicePairingFinished:(id)arg1 error:(int)arg2;	// IMP=0x00000000000082a1
- (void)devicePairingUserPasskeyNotification:(id)arg1 passkey:(unsigned int)arg2;	// IMP=0x0000000000008217
- (void)devicePairingKeypressNotification:(id)arg1 type:(unsigned long long)arg2;	// IMP=0x000000000000818d
- (void)devicePairingUserConfirmationRequest:(id)arg1 numericValue:(unsigned int)arg2;	// IMP=0x0000000000008103
- (void)devicePairingPINCodeRequest:(id)arg1;	// IMP=0x000000000000807c
- (void)devicePairingConnecting:(id)arg1;	// IMP=0x0000000000007ff5
- (void)devicePairingStarted:(id)arg1;	// IMP=0x0000000000007f6e

@end
