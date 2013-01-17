/*
 * xmlutils.c
 *
 *  Created on: 02.01.2013
 *      Author: Andrew Lichman
 */

#import "commonHeaders.h"


//
//void test(char * xml, char * xslt){
//    xmlDocPtr doc;
//    xmlXPathContextPtr xpath;
//    xmlXPathObjectPtr rez;
//    xmlChar * str;
//
//
//    doc = xmlParseDoc(str);
//    xpath = xmlXPathNewContext(doc);
//    rez = xmlXPathEvalExpression("/root/mc",xpath);
//    if(rez != NULL){
//       puts("Resalt");
//      xmlChar * z = xmlNodeListGetString(doc, rez->nodesetval->nodeTab[0]->xmlChildrenNode, 1);
//      free(z);
//    }
//    xmlXPathFreeObject(rez);
//    xmlXPathFreeContext(xpath);
//    xmlFreeDoc(doc);
//}

static void xslt_class_compile_style(void * this, char * style){
	xmlDocPtr xlt_doc = xmlParseDoc(style);
	xsltStylesheetPtr cur = xsltParseStylesheetDoc(xlt_doc);
	((xslt_class*)this)->stylesheet = cur;
}

static xmlChar * xslt_class_transform(void * this, char * xml){
	 xmlDocPtr doc, res;
			xmlChar *output;
			int len = 0 ;
			doc = xmlParseDoc(xml);

			res = xsltApplyStylesheet(((xslt_class*)this)->stylesheet, doc, NULL);
			xsltSaveResultToString(&output, &len, res, ((xslt_class*)this)->stylesheet);

			xmlFreeDoc(res);
			xmlFreeDoc(doc);
			return output;
}

static xmlChar * xslt_class_fast_transform(char * xml, char * xslt){
	    xsltStylesheetPtr cur = NULL;
		xmlDocPtr xlt_doc, doc, res;
		xmlChar *output;
		int len = 0 ;
		doc = xmlParseDoc(xml);
		xlt_doc = xmlParseDoc(xslt);

		cur = xsltParseStylesheetDoc(xlt_doc);
		res = xsltApplyStylesheet(cur, doc, NULL);
		xsltSaveResultToString(&output, &len, res, cur);

		xsltFreeStylesheet(cur);
		xmlFreeDoc(res);
		xmlFreeDoc(doc);

		return output;
}

static void xslt_free(void* this){
	xsltFreeStylesheet(((xslt_class*)this)->stylesheet);
	free(this);
}

xslt_class* xslt_class_new(){
     xslt_class * out = malloc(sizeof(xslt_class));

     out->compile_style = xslt_class_compile_style;
     out->transform = xslt_class_transform;
     out->fast_transform = xslt_class_fast_transform;
     out->free = xslt_free;

     return out;
}
