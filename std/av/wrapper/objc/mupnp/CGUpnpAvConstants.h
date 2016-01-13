//
//  CGUpnpAvConstants.h
//  CyberLink for C
//
//  Created by Satoshi Konno on 08/07/10.
//  Copyright 2008 Satoshi Konno. All rights reserved.
//

#ifndef CGUPNPAVCONSTANTS_H
#define CGUPNPAVCONSTANTS_H

#define CG_UPNPAV_UPNPCLASS_CONTAINER "object.container"
#define CG_UPNPAV_UPNPCLASS_ITEM "object.item"
#define CG_UPNPAV_UPNPCLASS_PHOTO "object.item.imageItem.photo"
#define CG_UPNPAV_UPNPCLASS_MOVIE "object.item.videoItem.movie"
#define CG_UPNPAV_UPNPCLASS_MUSIC "object.item.audioItem.musicTrack"

#define CG_UPNPAV_PROTOCOLINFO_AUDIO "http-get:*:audio/*:*"
#define CG_UPNPAV_PROTOCOLINFO_AUDIO_LPCM "http-get:*:audio/L16:DLNA.ORG_PN=LPCM;DLNA.ORG_OP=01;DLNA.ORG_FLAGS=01700000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_AUDIO_MP3 "http-get:*:audio/mpeg:DLNA.ORG_PN=MP3;DLNA.ORG_OP=01;DLNA.ORG_FLAGS=01700000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_AUDIO_MP4 "http-get:*:audio/mp4:*;DLNA.ORG_OP=01;DLNA.ORG_FLAGS=01700000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_AUDIO_FLAC "http-get:*:audio/x-flac:*;DLNA.ORG_OP=01;DLNA.ORG_FLAGS=01700000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_AUDIO_AIFF "http-get:*:audio/x-aiff:*;DLNA.ORG_OP=01;DLNA.ORG_FLAGS=01700000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_AUDIO_WAV "http-get:*:audio/wav:*;DLNA.ORG_OP=01;DLNA.ORG_FLAGS=01700000000000000000000000000000"

#define CG_UPNPAV_PROTOCOLINFO_VIDEO "http-get:*:video/*:*"
#define CG_UPNPAV_PROTOCOLINFO_VIDEO_MPEG_TS_SD_EU_ISO "http-get:*:video/mpeg:DLNA.ORG_PS=1;DLNA.ORG_CI=0;DLNA.ORG_OP=00;DLNA.ORG_PN=MPEG_TS_SD_EU_ISO;DLNA.ORG_FLAGS=ad300000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_VIDEO_AVC_TS_MP_SD_MPEG1_L3_ISO "http-get:*:video/mpeg:DLNA.ORG_PS=1;DLNA.ORG_CI=0;DLNA.ORG_OP=00;DLNA.ORG_PN=AVC_TS_MP_SD_MPEG1_L3_ISO;DLNA.ORG_FLAGS=ad300000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_VIDEO_AVC_TS_MP_HD_MPEG1_L3_ISO "http-get:*:video/mpeg:DLNA.ORG_PS=1;DLNA.ORG_CI=0;DLNA.ORG_OP=00;DLNA.ORG_PN=AVC_TS_MP_HD_MPEG1_L3_ISO;DLNA.ORG_FLAGS=ad300000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_VIDEO_AVC_TS_MP_HD_AC3_ISO "http-get:*:video/mpeg:DLNA.ORG_PS=1;DLNA.ORG_CI=0;DLNA.ORG_OP=00;DLNA.ORG_PN=AVC_TS_MP_HD_AC3_ISO;DLNA.ORG_FLAGS=ad300000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_VIDEO_AVC_TS_SD_EU_ISO "http-get:*:video/mpeg:DLNA.ORG_PS=1;DLNA.ORG_CI=0;DLNA.ORG_OP=00;DLNA.ORG_PN=AVC_TS_SD_EU_ISO;DLNA.ORG_FLAGS=ad300000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_VIDEO_AVC_TS_HD_EU_ISO "http-get:*:video/mpeg:DLNA.ORG_PS=1;DLNA.ORG_CI=0;DLNA.ORG_OP=00;DLNA.ORG_PN=AVC_TS_HD_EU_ISO;DLNA.ORG_FLAGS=ad300000000000000000000000000000"
#define CG_UPNPAV_PROTOCOLINFO_VIDEO_AVC_TS_HD_24_AC3_ISO "http-get:*:video/mpeg:DLNA.ORG_PN=AVC_TS_HD_24_AC3_ISO;SONY.COM_PN=AVC_TS_HD_24_AC3_ISO;DLNA.ORG_OP=01;DLNA.ORG_CI=0"
#define CG_UPNPAV_PROTOCOLINFO_VIDEO_AVC_TS_HD_50_AC3_ISO "http-get:*:video/mpeg:DLNA.ORG_PN=AVC_TS_HD_50_AC3_ISO;SONY.COM_PN=AVC_TS_HD_50_AC3_ISO;DLNA.ORG_OP=01;DLNA.ORG_CI=0"

#define CG_UPNPAV_PROTOCOL_IMAGE_JPEG @"http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_LRG;DLNA.ORG_OP=01;DLNA.ORG_FLAGS=01700000000000000000000000000000"

typedef enum
{
    DLNA_ORG_FLAG_SENDER_PACED               = (1 << 31),
    DLNA_ORG_FLAG_TIME_BASED_SEEK            = (1 << 30),
    DLNA_ORG_FLAG_BYTE_BASED_SEEK            = (1 << 29),
    DLNA_ORG_FLAG_PLAY_CONTAINER             = (1 << 28),
    DLNA_ORG_FLAG_S0_INCREASE                = (1 << 27),
    DLNA_ORG_FLAG_SN_INCREASE                = (1 << 26),
    DLNA_ORG_FLAG_RTSP_PAUSE                 = (1 << 25),
    DLNA_ORG_FLAG_STREAMING_TRANSFER_MODE    = (1 << 24),
    DLNA_ORG_FLAG_INTERACTIVE_TRANSFERT_MODE = (1 << 23),
    DLNA_ORG_FLAG_BACKGROUND_TRANSFERT_MODE  = (1 << 22),
    DLNA_ORG_FLAG_CONNECTION_STALL           = (1 << 21),
    DLNA_ORG_FLAG_DLNA_V15                   = (1 << 20)
} dlna_org_flags;

#endif // CGUPNPAVCONSTANTS_H