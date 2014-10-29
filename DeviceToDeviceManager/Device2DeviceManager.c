//
//  Device2DeviceManager.c
//  DeviceToDeviceManager
//
//  Created by Sam Marshall on 10/29/14.
//  Copyright (c) 2014 Sam Marshall. All rights reserved.
//

#include "Device2DeviceManager.h"

typedef uintptr_t* Pointer;
typedef uintptr_t* (*FunctionPointer)();

static CFArrayRef *_loadedPlugins;
struct plugin_funct {
	FunctionPointer init;
	FunctionPointer terminate;
	FunctionPointer start_advert;
	FunctionPointer stop_advert;
	FunctionPointer start_browse;
	FunctionPointer stop_browse;
	FunctionPointer start_resolve;
	FunctionPointer stop_resolve;
};
static struct plugin_funct _plugins[3];

int D2DInitialize(int arg0, int arg1, int arg2) {
	int result = 0;
	CFBundleRef d2dManager = CFBundleGetBundleWithIdentifier(CFSTR("com.apple.DeviceToDeviceManager"));
	if (d2dManager == NULL) {
		printf("D2D: failed to get the D2D bundle\n");
		return 1;
	}
	
	CFURLRef pluginPath = CFBundleCopyBuiltInPlugInsURL(d2dManager);
	if (pluginPath == NULL) {
		printf("D2D: failed to get the URL for D2D plugins\n");
		return 1;
	}
	
	*_loadedPlugins = CFBundleCreateBundlesFromDirectory(kCFAllocatorDefault, pluginPath, CFSTR("bundle"));
	CFRelease(pluginPath);
	if (_loadedPlugins == NULL) {
		printf("D2D: loading plugins failed.  Continuing with no transports\n");
		return 1;
	}
	
	
	
	for (CFIndex index = 0; index < CFArrayGetCount(*_loadedPlugins); index++) {
		CFTypeRef plugin = CFArrayGetValueAtIndex(*_loadedPlugins, index);
		CFDictionaryRef pluginInfo = CFBundleGetInfoDictionary(plugin);
		CFTypeRef transportType = CFDictionaryGetValue(pluginInfo, CFSTR("D2DTransportType"));
		CFTypeRef transportPlugin = CFDictionaryGetValue(pluginInfo, CFSTR("D2DTransportPlugin"));
		if (transportPlugin != NULL && transportType != NULL) {
			int type = 0;
			if (CFNumberGetValue(transportType, kCFNumberIntType, &type)) {
				if (type < 3) {
					FunctionPointer pointer = CFBundleGetDataPointerForName(plugin, transportPlugin);
					if (pointer != NULL) {
						result = pointer(arg0, arg1, arg2);
						if (result == 0) {
							_plugins[index].init = CFBundleGetDataPointerForName(plugin, CFSTR("Initialize"));
							_plugins[index].terminate = CFBundleGetDataPointerForName(plugin, CFSTR("Terminate"));
							_plugins[index].start_advert = CFBundleGetDataPointerForName(plugin, CFSTR("StartAdvertisingPair"));
							_plugins[index].stop_advert = CFBundleGetDataPointerForName(plugin, CFSTR("StopAdvertisingPair"));
							_plugins[index].start_browse = CFBundleGetDataPointerForName(plugin, CFSTR("StartBrowsingForKey"));
							_plugins[index].stop_browse = CFBundleGetDataPointerForName(plugin, CFSTR("StopBrowsingForKey"));
							_plugins[index].start_resolve = CFBundleGetDataPointerForName(plugin, CFSTR("StartResolvingPair"));
							_plugins[index].stop_resolve = CFBundleGetDataPointerForName(plugin, CFSTR("StopResolvingPair"));
						}
					}
					else {
						printf("Failed to get the plugin interface structure\n");
					}
				}
				else {
					printf("Unknown transport id %d\n",type);
				}
			}
			else {
				printf("Failed to get the transport ID\n");
			}
		}
		else {
			printf("Plugin is missing it's transport ID or Plugin\n");
		}
	}
	
	return result;
}

void _d2dStartAdvertisingPairOnTransport(CFDataRef data1, CFDataRef data2, CFIndex index) {
	if (index <= 2) {
		FunctionPointer pointer = _plugins[index].start_advert;
		if (pointer != NULL) {
			pointer();
		}
	}
}

void _d2dStopAdvertisingPairOnTransport(CFDataRef data1, CFDataRef data2, CFIndex index) {
	if (index <= 2) {
		FunctionPointer pointer = _plugins[index].stop_advert;
		if (pointer != NULL) {
			pointer();
		}
	}
}

void _d2dStartResolvingPairOnTransport(CFDataRef data1, CFDataRef data2, CFIndex index) {
	if (index <= 2) {
		FunctionPointer pointer = _plugins[index].start_resolve;
		if (pointer != NULL) {
			pointer();
		}
	}
}

void _d2dStopResolvingPairOnTransport(CFDataRef data1, CFDataRef data2, CFIndex index) {
	if (index <= 2) {
		FunctionPointer pointer = _plugins[index].stop_resolve;
		if (pointer != NULL) {
			pointer();
		}
	}
}

int D2DStartAdvertisingPair(UInt8 *bytes1, CFIndex length1, UInt8 *bytes2, CFIndex length2) {
	CFDataRef data1 = CFDataCreate(kCFAllocatorDefault, bytes1, length1);
	CFDataRef data2 = CFDataCreate(kCFAllocatorDefault, bytes2, length2);
	int result = 1;
	if ((data1 != 0x0) && (data2 != 0x0)) {
		for (CFIndex index = 0; index < 3; index++) {
			_d2dStartAdvertisingPairOnTransport(data1, data2, index);
		}
		CFRelease(data1);
		CFRelease(data2);
		result = 0;
	}
	return result;
}

int D2DStartAdvertisingPairOnTransport(UInt8 *bytes1, CFIndex length1, UInt8 *bytes2, CFIndex length2, CFIndex transport) {
	CFDataRef data1 = CFDataCreate(kCFAllocatorDefault, bytes1, length1);
	CFDataRef data2 = CFDataCreate(kCFAllocatorDefault, bytes2, length2);
	int result = 1;
	if ((data1 != 0x0) && (data2 != 0x0)) {
		_d2dStartAdvertisingPairOnTransport(data1, data2, transport);
		CFRelease(data1);
		CFRelease(data2);
		result = 0;
	}
	return result;
}

int D2DStopAdvertisingPair(UInt8 *bytes1, CFIndex length1, UInt8 *bytes2, CFIndex length2) {
	CFDataRef data1 = CFDataCreate(kCFAllocatorDefault, bytes1, length1);
	CFDataRef data2 = CFDataCreate(kCFAllocatorDefault, bytes2, length2);
	int result = 1;
	if ((data1 != 0x0) && (data2 != 0x0)) {
		for (CFIndex index = 0; index < 3; index++) {
			_d2dStopAdvertisingPairOnTransport(data1, data2, index);
		}
		CFRelease(data1);
		CFRelease(data2);
		result = 0;
	}
	return result;
}

int D2DStopAdvertisingPairOnTransport(UInt8 *bytes1, CFIndex length1, UInt8 *bytes2, CFIndex length2, CFIndex transport) {
	CFDataRef data1 = CFDataCreate(kCFAllocatorDefault, bytes1, length1);
	CFDataRef data2 = CFDataCreate(kCFAllocatorDefault, bytes2, length2);
	int result = 1;
	if ((data1 != 0x0) && (data2 != 0x0)) {
		_d2dStopAdvertisingPairOnTransport(data1, data2, transport);
		CFRelease(data1);
		CFRelease(data2);
		result = 0;
	}
	return result;
}

int D2DStartBrowsingForKey(UInt8 *bytes, CFIndex length) {
	CFDataRef data = CFDataCreate(kCFAllocatorDefault, bytes, length);
	int result = 0x1;
	if (data != NULL) {
		for (CFIndex index = 0; index < 3; index++) {
			FunctionPointer pointer = _plugins[index].start_browse;
			if (pointer != NULL) {
				pointer(data);
			}
		}
		CFRelease(data);
		result = 0x0;
	}
	return result;
}

int D2DStartBrowsingForKeyOnTransport(UInt8 *bytes, CFIndex length, CFIndex transport) {
	CFDataRef data = CFDataCreate(kCFAllocatorDefault, bytes, length);
	int result = 0x1;
	if (data != NULL) {
		if (transport < 3) {
			FunctionPointer pointer = _plugins[transport].start_browse;
			if (pointer != NULL) {
				pointer(data);
			}
		}
		CFRelease(data);
		result = 0x0;
	}
	return result;
}

int D2DStopBrowsingForKey(UInt8 *bytes, CFIndex length) {
	CFDataRef data = CFDataCreate(kCFAllocatorDefault, bytes, length);
	int result = 0x1;
	if (data != NULL) {
		for (CFIndex index = 0; index < 3; index++) {
			FunctionPointer pointer = _plugins[index].stop_browse;
			if (pointer != NULL) {
				pointer(data);
			}
		}
		CFRelease(data);
		result = 0x0;
	}
	return result;
}

int D2DStopBrowsingForKeyOnTransport(UInt8 *bytes, CFIndex length, CFIndex transport) {
	CFDataRef data = CFDataCreate(kCFAllocatorDefault, bytes, length);
	int result = 0x1;
	if (data != NULL) {
		if (transport < 3) {
			FunctionPointer pointer = _plugins[transport].stop_browse;
			if (pointer != NULL) {
				pointer(data);
			}
		}
		CFRelease(data);
		result = 0x0;
	}
	return result;
}


int D2DStartResolvingPair(UInt8 *bytes1, CFIndex length1, UInt8 *bytes2, CFIndex length2) {
	CFDataRef data1 = CFDataCreate(kCFAllocatorDefault, bytes1, length1);
	CFDataRef data2 = CFDataCreate(kCFAllocatorDefault, bytes2, length2);
	int result = 1;
	if ((data1 != 0x0) && (data2 != 0x0)) {
		for (CFIndex index = 0; index < 3; index++) {
			_d2dStartResolvingPairOnTransport(data1, data2, index);
		}
		CFRelease(data1);
		CFRelease(data2);
		result = 0;
	}
	return result;
}

int D2DStartResolvingPairOnTransport(UInt8 *bytes1, CFIndex length1, UInt8 *bytes2, CFIndex length2, CFIndex transport) {
	CFDataRef data1 = CFDataCreate(kCFAllocatorDefault, bytes1, length1);
	CFDataRef data2 = CFDataCreate(kCFAllocatorDefault, bytes2, length2);
	int result = 1;
	if ((data1 != 0x0) && (data2 != 0x0)) {
		if (transport < 3) {
			_d2dStartResolvingPairOnTransport(data1, data2, transport);
		}
		CFRelease(data1);
		CFRelease(data2);
		result = 0;
	}
	return result;
}


int D2DStopResolvingPair(UInt8 *bytes1, CFIndex length1, UInt8 *bytes2, CFIndex length2) {
	CFDataRef data1 = CFDataCreate(kCFAllocatorDefault, bytes1, length1);
	CFDataRef data2 = CFDataCreate(kCFAllocatorDefault, bytes2, length2);
	int result = 1;
	if ((data1 != 0x0) && (data2 != 0x0)) {
		for (CFIndex index = 0; index < 3; index++) {
			_d2dStopResolvingPairOnTransport(data1, data2, index);
		}
		CFRelease(data1);
		CFRelease(data2);
		result = 0;
	}
	return result;
}

int D2DStopResolvingPairOnTransport(UInt8 *bytes1, CFIndex length1, UInt8 *bytes2, CFIndex length2, CFIndex transport) {
	CFDataRef data1 = CFDataCreate(kCFAllocatorDefault, bytes1, length1);
	CFDataRef data2 = CFDataCreate(kCFAllocatorDefault, bytes2, length2);
	int result = 1;
	if ((data1 != 0x0) && (data2 != 0x0)) {
		if (transport < 3) {
			_d2dStopResolvingPairOnTransport(data1, data2, transport);
		}
		CFRelease(data1);
		CFRelease(data2);
		result = 0;
	}
	return result;
}

//int D2DRetain(CFAllocatorRef allc, CFTypeRef value) {
//	if (LODWORD(rsi) <= 0x2) {
//		rax = *(_plugins + LODWORD(rsi) * 0x8);
//		if (rax != 0x0) {
//			rax = *(rax + 0x40);
//			if (rax != 0x0) {
//				rax = (rax)();
//			}
//			else {
//				LODWORD(rax) = 0x2;
//				return rax;
//			}
//		}
//		else {
//			LODWORD(rax) = 0x2;
//			return rax;
//		}
//	}
//	else {
//		LODWORD(rax) = 0x2;
//		return rax;
//	}
//	return rax;
//}
//
//int D2DRelease(CFAllocatorRef allc, CFTypeRef value) {
//	if (LODWORD(rsi) <= 0x2) {
//		rax = *(_plugins + LODWORD(rsi) * 0x8);
//		if (rax != 0x0) {
//			rax = *(rax + 0x48);
//			if (rax != 0x0) {
//				rax = (rax)();
//			}
//			else {
//				LODWORD(rax) = 0x2;
//				return rax;
//			}
//		}
//		else {
//			LODWORD(rax) = 0x2;
//			return rax;
//		}
//	}
//	else {
//		LODWORD(rax) = 0x2;
//		return rax;
//	}
//	return rax;
//}

