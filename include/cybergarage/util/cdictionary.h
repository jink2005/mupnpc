/******************************************************************
*
*	CyberUtil for C
*
*	Copyright (C) Satoshi Konno 2005
*
*       Copyright (C) 2006 Nokia Corporation. All rights reserved.
*
*       This is licensed under BSD-style license,
*       see file COPYING.
*
*	File: cdictionary.h
*
*	Revision:
*
*	05/26/09
*		- first revision
*
******************************************************************/

#ifndef _CG_UTIL_CDICTIONARY_H_
#define _CG_UTIL_CDICTIONARY_H_

#include <cybergarage/typedef.h>
#include <cybergarage/util/clist.h>
#include <cybergarage/util/cstring.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
 * Define
 ****************************************/

/****************************************
 * Data Type
 ****************************************/

/**
 * \brief The generic wrapper struct for CyberLinkC's dictionarys.
 *
 * This wrapper has been created to enable 100% code
 * compatibility between different platforms (Linux, Win32 etc..)
 */
typedef struct _CgDictionary {
	BOOL headFlag;
	struct _CgDictionary *prev;
	struct _CgDictionary *next;
	CgString *key;
	CgString *value;
} CgDictionaryElement, CgDictionary;

/****************************************
* Function
****************************************/

/**
 * Create a new dictionary
 */
CgDictionaryElement *cg_dictionary_element_new();

/**
 * Destroy a dictionary.
 *
 * \param dictionary Dictionary to destroy
 */
BOOL cg_dictionary_element_delete(CgDictionaryElement *dictionary);

/**
 * Set a key
 *
 * \param dictionary Dictionary struct
 * \param name String to set 
 */
#define cg_dictionary_element_setkey(dictionary, name) cg_string_setvalue(dictionary->key, name)
/**
 * Get a key
 *
 * \param dictionary Dictionary struct
 */
#define cg_dictionary_element_getkey(dictionary) cg_string_getvalue(dictionary->key)

/**
 * Set a value
 *
 * \param dictionary Dictionary struct
 * \param value String to set
 */
#define cg_dictionary_element_setvalue(dictionary, val) cg_string_setvalue(dictionary->key, val)
/**
 * Get a value
 *
 * \param dictionary Dictionary struct
 */
#define cg_dictionary_element_getvalue(dictionary) cg_string_getvalue(dictionary->key)

#define cg_dictionary_element_next(dictionary) (CgDictionaryElement *)cg_list_next((CgList *)dictionary)
#define cg_dictionary_element_remove(dictionary) cg_list_remove((CgList *)dictionary)

/****************************************
* Function (Dictionary List)
****************************************/

/**
 * Create a new dictionary list
 *
 * \return Dictionary list
 */
CgDictionary *cg_dictionary_new();

/**
 * Destroy a dictionary list
 *
 * \param dictionaryList The dictionary list in question
 */
void cg_dictionary_delete(CgDictionary *dictionaryList);

/**
 * Clear the contents of a dictionary list
 *
 * \param dictionaryList Dictionary list in question
 */
#define cg_dictionary_clear(dictionaryList) cg_list_clear((CgList *)dictionaryList, (CG_LIST_DESTRUCTORFUNC)cg_dictionary_element_delete)

/**
 * Get the size of a dictionary list
 *
 * \param dictionaryList The dictionary list in question
 */
#define cg_dictionary_size(dictionaryList) cg_list_size((CgList *)dictionaryList)

/**
 * Get the first actual item from a dictionary list to use as an iterator
 *
 * \param dictionaryList The dictionary list in question
 */
#define cg_dictionary_gets(dictionaryList) (CgDictionaryElement *)cg_list_next((CgList *)dictionaryList)

/**
 * Add a dictionary into a dictionary list
 *
 * \param dictionaryList The dictionary list in question
 * \param dictionary The dictionary to add to the list
 */
#define cg_dictionary_add(dictionaryList, dictionary) cg_list_add((CgList *)dictionaryList, (CgList *)dictionary)

/**
 * Remove a dictionary from dictionary list
 *
 * \param dictionaryList The dictionary list in question
 * \param dictionary The dictionary to be removed 
 */
#define cg_dictionary_remove(dictionary) cg_list_remove((CgList *)dictionary)

#ifdef  __cplusplus

} /* extern "C" */

#endif

#endif