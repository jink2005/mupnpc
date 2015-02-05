/******************************************************************
 *
 * mUPnP for C
 *
 * Copyright (C) Satoshi Konno 2005
 * Copyright (C) 2006 Nokia Corporation. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/action.h>
#include <mupnp/util/log.h>

/****************************************
* mupnp_upnp_action_new
****************************************/

mUpnpUpnpActionList *mupnp_upnp_actionlist_new()
{
	mUpnpUpnpAction *actionList;

	mupnp_log_debug_l4("Entering...\n");

	actionList = (mUpnpUpnpAction *)malloc(sizeof(mUpnpUpnpAction));

	if ( NULL != actionList )
		mupnp_list_header_init((mUpnpList *)actionList);

	return actionList;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_upnp_action_delete
****************************************/

void mupnp_upnp_actionlist_delete(mUpnpUpnpActionList *actionList)
{
	mupnp_log_debug_l4("Entering...\n");

	mupnp_list_remove((mUpnpList *)actionList);
	free(actionList);

	mupnp_log_debug_l4("Leaving...\n");
}
