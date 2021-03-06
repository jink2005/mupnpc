//
//  CGUpnpAvController.h
//  CyberLink for C
//
//  Created by Satoshi Konno on 08/06/25.
//  Copyright 2008 Satoshi Konno. All rights reserved.
//

#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>
#import <Foundation/NSIndexPath.h>

#import <mUPnP/CGUpnpControlPoint.h>

@class CGUpnpAvServer;
@class CGUpnpAvObject;
@class CGUpnpAvRenderer;
@class DMRMediaItem;


@protocol CGUpnpAvControllerDelegate;

/**
 * The CGUpnpControlPoint class is a wrapper class for CgUpnpControlPoint of CyberLink for C to 
 * program using only Objective-C directly on MacOSX.
 * Currently, the only basic methods are wrapped to control UPnP devices.
 */
@interface CGUpnpAvController : CGUpnpControlPoint 
{
}

@property (nonatomic, weak) id<CGUpnpAvControllerDelegate> avDelegate;
/**
 * Activate some background threads of the control point such as SSDP and 
 * HTTP servers to listen messages and events of UPnP. You must call this 
 * method before you can actually use a control point.
 *
 * @return TRUE if successful; otherwise FALSE
 *
 */
- (NSArray *)servers;
- (CGUpnpAvServer *)serverForUDN:(NSString *)aUdn;
- (CGUpnpAvServer *)serverForFriendlyName:(NSString *)aFriendlyName;
- (CGUpnpAvServer *)serverForPath:(NSString *)aPath;
- (CGUpnpAvServer *)serverForIndexPath:(NSIndexPath *)aIndexPath;
- (CGUpnpAvObject *)objectForTitlePath:(NSString *)aServerAndTitlePath;
- (CGUpnpAvObject *)objectForIndexPath:(NSIndexPath *)aServerAndTitleIndexPath;
- (NSArray *)browseDirectChildrenWithTitlePath:(NSString *)aServerAndTitlePath;
- (NSArray *)browseDirectChildrenWithIndexPath:(NSIndexPath *)aServerAndTitleIndexPath;

- (NSArray *)renderers;
- (CGUpnpAvRenderer *)rendererForUDN:(NSString *)aUdn;
- (CGUpnpAvRenderer *)rendererWithSubscriptionID:(NSString *)sid;

- (void)search;
- (BOOL)subscribeEventNotificationFromDevice:(CGUpnpAvRenderer *)renderer;
- (BOOL)unsubscribeEventNotificationFromDevice:(CGUpnpAvRenderer *)renderer;

@end


@protocol CGUpnpAvControllerDelegate <NSObject, CGUpnpControlPointDelegate>

@optional
- (void)upnpAvController:(CGUpnpAvController *)controller didRendererPositionInfoUpdated:(CGUpnpAvRenderer *)renderer;
- (void)upnpAvController:(CGUpnpAvController *)controller didRendererPlaybackStateUpdated:(CGUpnpAvRenderer *)renderer;
- (void)upnpAvController:(CGUpnpAvController *)controller didRendererTrackURIUpdated:(CGUpnpAvRenderer *)renderer;
- (void)upnpAvController:(CGUpnpAvController *)controller didRendererTrackDurationUpdated:(CGUpnpAvRenderer *)renderer;
- (void)upnpAvController:(CGUpnpAvController *)controller didRendererVolumeUpdated:(CGUpnpAvRenderer *)renderer;
- (void)upnpAvController:(CGUpnpAvController *)controller didRenderer:(CGUpnpAvRenderer *)renderer preparingToPlayItem:(DMRMediaItem *)item;
@end