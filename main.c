/*
 * main.c
 *
 *  Created on: 30.12.2012
 *      Author: Andrew Lichman
 */

#include "commonHeaders.h";


int main (int argc, const char * argv[])
{
    xslt_class * x = xslt_class_new();
    x->compile_style_file(x,"/Users/sdads/Documents/workspace_juno/ZeroCacheEngine/test.xsl");
    xmlChar * dd = x->transform_file(x,"/Users/sdads/Documents/workspace_juno/ZeroCacheEngine/test.xml");
    printf("Finish : %s \n",dd);
    free(dd);

    x->free;

     dbcache_class * db = dbcache_class_new();
     db->open();
     db->free(db);
}
