/*
 * main.c
 *
 *  Created on: 30.12.2012
 *      Author: Andrew Lichman
 */

#include "commonHeaders.h";


int main (int argc, const char * argv[])
{
	 xslt_class_unit_test();
     dbcache_class * db = dbcache_class_new();
     db->open();
     db->free(db);
}
