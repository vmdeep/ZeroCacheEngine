/*
 * xmlutils.h
 *
 *  Created on: 02.01.2013
 *      Author: Andrew Lichman
 */

#ifndef XMLUTILS_H_
#define XMLUTILS_H_

typedef struct xslt_class{
	void (*free)(void*);
    void (*compile_style)(void*,char *);
    xmlChar* (*transform)(void*,char*);
    xmlChar* (*fast_transform)(char*,char*);
    xsltStylesheetPtr stylesheet;
} xslt_class;

xslt_class* xslt_class_new();


#endif /* XMLUTILS_H_ */
