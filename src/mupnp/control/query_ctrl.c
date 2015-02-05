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

#include <mupnp/control/control.h>
#include <mupnp/util/log.h>

/****************************************
* MUPNP_NOUSE_QUERY (Begin)
****************************************/

#if !defined(MUPNP_NOUSE_QUERYCTRL)

/****************************************
* mupnp_upnp_action_performlistener
****************************************/

BOOL mupnp_upnp_statevariable_performlistner(mUpnpUpnpStateVariable *statVar, mUpnpUpnpQueryRequest *queryReq)
{
	MUPNP_STATEVARIABLE_LISTNER	 listener;
	mUpnpUpnpQueryResponse *queryRes;
	mUpnpHttpRequest *queryReqHttpReq;
	mUpnpHttpResponse *queryResHttpRes;
	
	mupnp_log_debug_l4("Entering...\n");

	listener = mupnp_upnp_statevariable_getlistener(statVar);
	if (listener == NULL)
		return FALSE;
	
	queryRes = mupnp_upnp_control_query_response_new();

	mupnp_upnp_statevariable_setstatuscode(statVar, MUPNP_STATUS_INVALID_ACTION);
	mupnp_upnp_statevariable_setstatusdescription(statVar, mupnp_upnp_status_code2string(MUPNP_STATUS_INVALID_ACTION));
	mupnp_upnp_statevariable_setvalue(statVar, "");
	
	if (listener(statVar) == TRUE)
		mupnp_upnp_control_query_response_setresponse(queryRes, statVar);
	else
		mupnp_upnp_control_soap_response_setfaultresponse(mupnp_upnp_control_query_response_getsoapresponse(queryRes), mupnp_upnp_statevariable_getstatuscode(statVar), mupnp_upnp_statevariable_getstatusdescription(statVar));
	
	queryReqHttpReq = mupnp_soap_request_gethttprequest(mupnp_upnp_control_query_request_getsoaprequest(queryReq));
	queryResHttpRes = mupnp_soap_response_gethttpresponse(mupnp_upnp_control_query_response_getsoapresponse(queryRes));
	mupnp_http_request_postresponse(queryReqHttpReq, queryResHttpRes);	

	mupnp_upnp_control_query_response_delete(queryRes);
	
	mupnp_log_debug_l4("Leaving...\n");

	return TRUE;
}

/****************************************
* mupnp_upnp_statevariable_post
****************************************/

BOOL mupnp_upnp_statevariable_post(mUpnpUpnpStateVariable *statVar)
{
	mUpnpUpnpQueryRequest *queryReq;
	mUpnpUpnpQueryResponse *queryRes;
	BOOL querySuccess;
	
	mupnp_log_debug_l4("Entering...\n");

	queryReq = mupnp_upnp_control_query_request_new();
	
	mupnp_upnp_control_query_request_setstatevariable(queryReq, statVar);
	queryRes = mupnp_upnp_control_query_request_post(queryReq);
	querySuccess = mupnp_upnp_control_query_response_issuccessful(queryRes);
	mupnp_upnp_statevariable_setvalue(statVar, (querySuccess == TRUE) ? mupnp_upnp_control_query_response_getreturnvalue(queryRes) : "");
	
	mupnp_upnp_control_query_request_delete(queryReq);
	
	mupnp_log_debug_l4("Leaving...\n");

	return querySuccess;
}

/****************************************
* MUPNP_NOUSE_QUERY (End)
****************************************/

#endif
