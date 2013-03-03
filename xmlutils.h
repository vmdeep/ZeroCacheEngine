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
    void (*compile_style_file)(void*,char*);
    xmlChar* (*transform)(void*,char*);
    xmlChar* (*transform_file)(void*,char*);
    xmlChar* (*fast_transform)(char*,char*);
    xsltStylesheetPtr stylesheet;
    char * params[];
} xslt_class;

xslt_class* xslt_class_new();

void xslt_class_unit_stress_test();

void xslt_class_unit_test();

#endif /* XMLUTILS_H_ */
