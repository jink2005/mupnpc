//
//  CGUpnpAvController.m
//  CyberLink for C
//
//  Created by Satoshi Konno on 08/06/25.
//  Copyright 2008 Satoshi Konno. All rights reserved.
//

#include <mupnp/ssdp/ssdp.h>
#include <mupnp/std/av/cmediaserver.h>

#import "CGUpnpAvController.h"
#import "CGUpnpAvServer.h"
#import "CGUpnpAvConstants.h"
#import "CGXml.h"
#import "CGXmlNode.h"
#import "CGUpnpAvObject.h"
#import "CGUpnpAvContainer.h"
#import "CGUpnpAvRenderer.h"

@implementation CGUpnpAvController

- (id)init
{
	if ((self = [super init]) == nil)
		return nil;
	
	[self setSsdpSearchMX:1];
	
	return self;
}

- (void)dealloc
{
}

////////////////////////////////////////////////////////////
// Media Server
////////////////////////////////////////////////////////////

- (NSArray *)servers;
{
	NSArray *devices = [self devices];
	NSMutableArray *serverArray = [[NSMutableArray alloc] init];

	for (CGUpnpDevice *dev in devices) {
		if (![dev isDeviceType:@CG_UPNPAV_DMS_DEVICE_TYPE])
			continue;
		CGUpnpAvServer *server = nil;		
		void *devData = [dev userData];
		if (!devData) {
			mUpnpDevice *cDevice = [dev cObject];
			if (!cDevice)
				continue;
			server = [[CGUpnpAvServer alloc] initWithCObject:(__bridge CgUpnpDevice *)(cDevice)];
			[server setUserObject:server];
		}
		else
			server = (CGUpnpAvServer *)((__bridge id)devData);
		if (server == nil)
			continue;
		[serverArray addObject:server];
	}
	return serverArray;
}

- (CGUpnpAvServer *)serverForUDN:(NSString *)aUdn
{
	if (aUdn == nil)
		return nil;
	NSArray *servers = [self servers];
	for (CGUpnpAvServer *server in servers) {
		if ([server isUDN:aUdn])
			return server;
	}
	return nil;
}

- (CGUpnpAvServer *)serverForFriendlyName:(NSString *)aFriendlyName
{
	if (aFriendlyName == nil)
		return nil;
	NSArray *servers = [self servers];
	for (CGUpnpAvServer *server in servers) {
		if ([server isFriendlyName:aFriendlyName])
			return server;
	}
	return nil;
}

- (CGUpnpAvServer *)serverForPath:(NSString *)aPath;
{
	NSArray *srvAndObjPathArray = [aPath pathComponents];
	if ([srvAndObjPathArray count] <= 0)
		return nil;
	if ([aPath isAbsolutePath] && ([srvAndObjPathArray count] <= 1))
		return nil;
	NSString *avSrvName = [CGXml unescapestring:[aPath isAbsolutePath] ? [srvAndObjPathArray objectAtIndex:1] : [srvAndObjPathArray objectAtIndex:0]];
	return [self serverForFriendlyName:avSrvName];
}

- (CGUpnpAvServer *)serverForIndexPath:(NSIndexPath *)aIndexPath
{
	NSUInteger idxCnt = [aIndexPath length];
	if (idxCnt < 1)
		return nil;
	
	NSArray *servers = [self servers];
	NSUInteger serverNum = [aIndexPath indexAtPosition:0];
	if ([servers count] <= serverNum)
		return nil;
	
	return [servers objectAtIndex:serverNum];
}

- (CGUpnpAvObject *)objectForTitlePath:(NSString *)aServerAndTitlePath
{
	CGUpnpAvServer *avSrv = [self serverForPath:aServerAndTitlePath];
	if (avSrv == nil)
		return nil;

	NSMutableArray *titlePathArray = [NSMutableArray arrayWithArray:[aServerAndTitlePath pathComponents]];
	[titlePathArray removeObjectAtIndex:0];
	if (aServerAndTitlePath.isAbsolutePath)
		[titlePathArray removeObjectAtIndex:0];

	NSString *titlePath = [NSString pathWithComponents:titlePathArray];
	CGUpnpAvObject *avObj = [avSrv objectForTitlePath:titlePath];
	
	return avObj;
}

- (CGUpnpAvObject *)objectForIndexPath:(NSIndexPath *)aServerAndTitleIndexPath
{
	CGUpnpAvServer *avSrv = [self serverForIndexPath:aServerAndTitleIndexPath];
	if (!avSrv)
		return nil;
	
	CGUpnpAvContainer*rootObj = [avSrv rootObject];
	if (!rootObj)
		return nil;

	CGUpnpAvObject *avObj = rootObj;
	NSUInteger idxPathLength = [aServerAndTitleIndexPath length];
	NSUInteger n;
	for (n=1; n<idxPathLength; n++) {
		if ([avObj isItem])
			return nil;
		CGUpnpAvContainer *avCon = (CGUpnpAvContainer *)avObj;
		NSUInteger avObjIdx = [aServerAndTitleIndexPath indexAtPosition:n];
		avObj = [avCon childAtIndex:avObjIdx];
		NSLog(@"objectForIndexPath = [%tu/%tu][%tu/%tu] %@ (%@)", n, idxPathLength, avObjIdx,  [avCon childCount], [avObj title], [avObj objectId]);
		if (!avObj)
			return nil;
	}
	
	
	return avObj;
}

- (NSArray *)browseDirectChildrenWithTitlePath:(NSString *)aServerAndTitlePath
{
	CGUpnpAvServer *avSrv = [self serverForPath:aServerAndTitlePath];
	if (avSrv == nil)
		return nil;
	
	CGUpnpAvObject *avObj = [self objectForTitlePath:aServerAndTitlePath];
	if (avObj == nil)
		return nil;
	
	return [avSrv browseDirectChildren:[avObj objectId]];
}

- (NSArray *)browseDirectChildrenWithIndexPath:(NSIndexPath *)aServerAndTitleIndexPath
{
	CGUpnpAvServer *avSrv = [self serverForIndexPath:aServerAndTitleIndexPath];
	if (avSrv == nil)
		return nil;
	
	CGUpnpAvObject *avObj = [self objectForIndexPath:aServerAndTitleIndexPath];
	if (avObj == nil)
		return nil;

	return [avSrv browseDirectChildren:[avObj objectId]];
}

////////////////////////////////////////////////////////////
// Media Renderer
////////////////////////////////////////////////////////////

- (NSArray *)renderers;
{
	NSArray *devices = [self devices];
	NSMutableArray *rendererrArray = [[NSMutableArray alloc] init];
	
	for (CGUpnpDevice *dev in devices) {
		if (![dev isDeviceType:@CG_UPNPAV_DMR_DEVICE_TYPE])
			continue;
		mUpnpDevice *cDevice = [dev cObject];
		if (!cDevice)
			continue;
		CGUpnpAvRenderer *renderer = [[CGUpnpAvRenderer alloc] initWithCObject:cDevice];
		if (renderer == nil)
			continue;
		[rendererrArray addObject:renderer];
        [self subscribeEventNotificationFromDevice:renderer];
	}
	return rendererrArray;
}

- (CGUpnpAvRenderer *)rendererForUDN:(NSString *)aUdn
{
	if (aUdn == nil)
		return nil;
	NSArray *renderers = [self renderers];
	for (CGUpnpAvRenderer *renderer in renderers) {
		if ([renderer isUDN:aUdn])
			return renderer;
	}
	return nil;
}

////////////////////////////////////////////////////////////
// Search
////////////////////////////////////////////////////////////

- (void)search
{
	[super search];
#if defined(CG_UPNPAVCONTROLLER_SERCH_DEVICETYPES)
	[super searchWithST:[NSString stringWithUTF8String:CG_UPNPAV_DMS_DEVICE_TYPE]];
	[super searchWithST:[NSString stringWithUTF8String:CG_UPNPAV_DMR_DEVICE_TYPE]];
#endif
}

- (BOOL)subscribeEventNotificationFromDevice:(CGUpnpAvRenderer *)renderer
{
    BOOL bRet = YES;
    
    CGUpnpService *renderingControlService = [renderer renderControlService];
    if (renderingControlService) {
        bRet &= [super subscribeEventNotificationFromService:renderingControlService];
    }
    
    CGUpnpService *transportService = [renderer transportService];
    if (transportService) {
        bRet &= [super subscribeEventNotificationFromService:transportService];
    }
    
    CGUpnpService *connectionManagerService = [renderer connectionManagerService];
    if (connectionManagerService) {
        bRet &= [super subscribeEventNotificationFromService:connectionManagerService];
    }
    
    return bRet;
}

- (BOOL)unsubscribeEventNotificationFromDevice:(CGUpnpAvRenderer *)renderer
{
    BOOL bRet = YES;
    
    CGUpnpService *renderingControlService = [renderer renderControlService];
    if (renderingControlService) {
        bRet &= [super unsubscribeEventNotificationFromService:renderingControlService];
    }
    
    CGUpnpService *transportService = [renderer transportService];
    if (transportService) {
        bRet &= [super unsubscribeEventNotificationFromService:transportService];
    }
    
    CGUpnpService *connectionManagerService = [renderer connectionManagerService];
    if (connectionManagerService) {
        bRet &= [super unsubscribeEventNotificationFromService:connectionManagerService];
    }
    
    return bRet;
}

@end

