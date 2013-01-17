/*
 * unit_test.c
 *
 *  Created on: 08.01.2013
 *      Author: sdads
 */


#include "commonHeaders.h";


static xsltStylesheetPtr xsl_t;
static xslt_class * xsl_p;

void xslt_stress(){
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

void task1(void *ptr){
	//char xsl[340] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\"><xsl:template match=\"/\"><xsl:apply-templates></xsl:apply-templates></xsl:template><xsl:template match=\"/root/ch1/ch2\"><xsl:value-of select=\"./caption1\"></xsl:value-of></xsl:template></xsl:stylesheet>\0";
	int c = 1;
	char xml[80] = "<root><ch1><ch2><caption> task1 </caption></ch2></ch1></root>\0";
	xslt_class * s = xslt_class_new();
	while(c<3000){
		xmlChar * dd	= xsl_p->transform(xsl_p,&xml);
		printf("Finish task1: %s",dd);
		free(dd);
		c++;
	}

}

void task2(void *ptr){
	//char xsl[340] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\"><xsl:template match=\"/\"><xsl:apply-templates></xsl:apply-templates></xsl:template><xsl:template match=\"/root/ch1/ch2\"><xsl:value-of select=\"./caption2\"></xsl:value-of></xsl:template></xsl:stylesheet>\0";
	int c = 1;
	char xml[80] = "<root><ch1><ch2><caption> task2 </caption></ch2></ch1></root>\0";
	while(c<1000){
		xmlChar * dd	= xsl_p->transform(xsl_p,&xml);
		printf("Finish task2: %s",dd);
		free(dd);
		c++;
	}

}

void task3(void *ptr){
	puts("ok");
}

void xslt_test(){
	char xsl[500] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\"><xsl:output method=\"text\"/><xsl:template match=\"/\"><xsl:apply-templates></xsl:apply-templates></xsl:template><xsl:template match=\"/root/ch1/ch2\"><xsl:value-of select=\"./caption\"></xsl:value-of></xsl:template></xsl:stylesheet>\0";
		//xsl_t = m_compile_xslt(xsl);
		xsl_p = xslt_class_new();
		xsl_p->compile_style(xsl_p,&xsl);
		puts("finish");
		/*int y ;
	   y = 1;
	   scanf("%i",&y);
		while(y < 3){

			int i;
			for(i=0; i < 1; i++){
				xslt_test();
			}
			puts("Finish \n");
			scanf("%i",&y);
		}*/

	//	xslt_test();
	 //   puts("%-(");
	   struct threadpool *pool;
		pool = threadpool_init(2);
		int et = threadpool_add_task(pool,task1,NULL,0);
		et = threadpool_add_task(pool,task2,NULL,0);
		puts("next");
	    while(1){sleep(1);}
		return EXIT_SUCCESS;
}

