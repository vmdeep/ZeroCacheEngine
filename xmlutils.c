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
			char *params[16 + 1];
			params[0] = "test";
			params[1] = "123";
			params[2] = NULL;
			res = xsltApplyStylesheet(((xslt_class*)this)->stylesheet, doc, params);
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

static void xslt_class_free(void* this){
	xsltFreeStylesheet(((xslt_class*)this)->stylesheet);
	free(this);
}


xslt_class* xslt_class_new(){
     xslt_class * out = malloc(sizeof(xslt_class));

     out->compile_style = xslt_class_compile_style;
     out->transform = xslt_class_transform;
     out->fast_transform = xslt_class_fast_transform;
     out->free = xslt_class_free;

     return out;
}


void xslt_class_unit_stress_test(){
	        char  xml[4000000];
			char xsl[1000] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\"><xsl:template match=\"/\"><xsl:apply-templates></xsl:apply-templates></xsl:template><xsl:template match=\"/root/ch1/ch2\"><xsl:value-of select=\"./caption\"></xsl:value-of></xsl:template></xsl:stylesheet>\0";
			strcpy(xml,"<root>");
			int i;
			for (i = 0;  i < 10000; ++ i) {
				strcat(xml, "<ch1><ch2><caption> Stress Test for XML XSLT  </caption></ch2></ch1>");
			}
			strcat(xml,"</root>\0");
			xslt_class * s = xslt_class_new();
			xmlChar * dd	= s->fast_transform(&xml,&xsl);
			puts(dd);
			free(dd);
			s->free;
}

void xslt_class_unit_test(){
	    char xsl[500] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\"><xsl:output method=\"text\"/><xsl:template match=\"/\"><xsl:apply-templates></xsl:apply-templates></xsl:template><xsl:template match=\"/root/ch1/ch2\"><xsl:value-of select=\"./caption\"></xsl:value-of></xsl:template></xsl:stylesheet>\0";
	    xslt_class * xsl_p = xslt_class_new();
		xsl_p->compile_style(xsl_p,&xsl);
		int c = 1;
			char xml[80] = "<root><ch1><ch2><caption>Task</caption></ch2></ch1></root>\0";
			while(c<3000){
				xmlChar * dd	= xsl_p->transform(xsl_p,&xml);
				printf("Finish : %s \n",dd);
				free(dd);
				c++;
			}
		xsl_p->free(xsl_p);
}
