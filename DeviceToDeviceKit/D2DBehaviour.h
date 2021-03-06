//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//

#import "NSObject.h"

@class NSString;

@interface D2DBehaviour : NSObject
{
    NSString *name;	// 8 = 0x8
    id target;	// 16 = 0x10
    SEL action;	// 24 = 0x18
}

+ (id)behaviourWithName:(id)arg1 target:(id)arg2 action:(SEL)arg3;	// IMP=0x0000000000018cd7
@property SEL action; // @synthesize action;
@property(retain) id target; // @synthesize target;
@property(retain) NSString *name; // @synthesize name;
- (BOOL)performBehaviour:(id *)arg1;	// IMP=0x0000000000018dbe
- (id)initWithName:(id)arg1 target:(id)arg2 action:(SEL)arg3;	// IMP=0x0000000000018d34

@end

