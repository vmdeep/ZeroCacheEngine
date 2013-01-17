/*
 * main.c
 *
 *  Created on: 30.12.2012
 *      Author: Andrew Lichman
 */

#include "commonHeaders.h";


int main (int argc, const char * argv[])
{
	        char xsl[500] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\"><xsl:output method=\"text\"/><xsl:template match=\"/\"><xsl:apply-templates></xsl:apply-templates></xsl:template><xsl:template match=\"/root/ch1/ch2\"><xsl:value-of select=\"./caption\"></xsl:value-of></xsl:template></xsl:stylesheet>\0";
	        char xml[80] = "<root><ch1><ch2><caption> task2 </caption></ch2></ch1></root>\0";
			xslt_class * s = xslt_class_new();
			s->compile_style(s,&xsl);
			puts(s->transform(s,&xml));
			xslt_test();
}
