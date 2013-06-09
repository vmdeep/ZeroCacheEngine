/*
 * main.c
 *
 *  Created on: 30.12.2012
 *      Author: Andrew Lichman
 */

#include "commonHeaders.h";

int main (int argc, const char * argv[])
{
   // xslt_class * x = xslt_class_new();
  //  x->compile_style_file(x,"/Users/sdads/Documents/workspace_juno/ZeroCacheEngine/test.xsl");
  //  xmlChar * dd = x->transform_file(x,"/Users/sdads/Documents/workspace_juno/ZeroCacheEngine/test.xml");
  //  printf("Finish : %s \n",dd);
  //  free(dd);
  //  x->free;


	dbcache_class * db = dbcache_class_new("/Users/sdads/Documents/workspace_juno/ZeroCacheEngine/db2.txt");
	for(int i = 1; i<= 100000;i++){
		char * key = malloc(100);
		sprintf(key,"key_%d",i);

		char * dat = malloc(100);
		sprintf(dat,"data_%d",i);
		db->put(db,key,dat);
	}

    char * out = db->get(db,"key_100000");
    if(out != NULL){
    	printf("Resalt: %s", out);
    	free(out);
    }

	db->free(db);
}


