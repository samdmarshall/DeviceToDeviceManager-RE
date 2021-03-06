//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//

#import "NSObject.h"

@class NSError;

@protocol D2DPairingDelegate <NSObject>

@optional
- (void)simplePairing:(id <D2DPeer>)arg1 status:(unsigned char)arg2;
- (void)pairingKeypressNotification:(id <D2DPeer>)arg1 type:(unsigned long long)arg2;
- (void)pairingComplete:(id <D2DPeer>)arg1 error:(NSError *)arg2;
- (void)pairingUserPasskeyNotification:(id <D2DPeer>)arg1 passkey:(unsigned long long)arg2;
- (void)pairingUserConfirmationRequest:(id <D2DPeer>)arg1 numericValue:(unsigned long long)arg2;
- (void)pairingPINCodeRequest:(id <D2DPeer>)arg1;
- (void)pairingKeyEvent:(id <D2DPeer>)arg1 eventType:(int)arg2;
- (void)pairingConnecting:(id <D2DPeer>)arg1;
- (void)pairingStarted:(id <D2DPeer>)arg1;
@end

