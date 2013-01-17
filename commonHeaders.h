/*
 * commonHeaders.h
 *
 *  Created on: 30.12.2012
 *      Author: Andrew Lichman
 */

#ifndef COMMONHEADERS_H_
#define COMMONHEADERS_H_

typedef char * String;
typedef void * (*method_simple)(void *,void *);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlversion.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
#include <libxml/tree.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include "threadpool.h"
#include "xmlutils.h"
#include  "unit_test.h"
//#include "bson.h"
#include  <db.h>




#endif /* COMMONHEADERS_H_ */
