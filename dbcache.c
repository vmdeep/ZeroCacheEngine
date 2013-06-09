/*
 * dbcache.c
 *
 *  Created on: 18.01.2013
 *      Author: Andrew Lichman
 */
#import "commonHeaders.h"


static void dbcache_free(void* this){
	((dbcache_class*)this)->tindex->close(((dbcache_class*)this)->tindex,0);
	((dbcache_class*)this)->db->close(((dbcache_class*)this)->db,0);
	((dbcache_class*)this)->store->close(((dbcache_class*)this)->store,0);
	free(this);
}

static void dbcache_put(void* this, char * inkey, char * invalue){
	DBT key, data;
	memset(&key, 0, sizeof(DBT));
	memset(&data, 0, sizeof(DBT));

	key.data = inkey;
	key.size = strlen(inkey) +1;

	data.data = invalue;
	data.size = strlen(invalue) +1;

	int r = ((dbcache_class*)this)->db->put(((dbcache_class*)this)->db,NULL,&key,&data,0);
	int r = ((dbcache_class*)this)->store->put(((dbcache_class*)this)->store,NULL,&key,&data,0);
	if(r != 0)((dbcache_class*)this)->db->err(((dbcache_class*)this)->db,r,"dbcache_put");
}

static char * dbcache_get(void* this, char * inkey){
	DBT key, data;

	memset(&key, 0, sizeof(DBT));
	memset(&data, 0, sizeof(DBT));

	key.data = inkey;
	key.size = strlen(inkey) +1;

	int r = ((dbcache_class*)this)->db->get(((dbcache_class*)this)->db,NULL,&key,&data,0);
	if(r == 0){
		char * out = malloc(data.size);
		memcpy(out,data.data,data.size);
		return out;
	}
	((dbcache_class*)this)->db->err(((dbcache_class*)this)->db,r,"dbcache_get");
	return NULL;
}

int dbcache_secondary_key(DB *sdbp,const DBT *pkey,const DBT *pdata,DBT *skey){
	printf("sec");
	return 1;
}

dbcache_class * dbcache_class_new(char *filename){
	dbcache_class * out = malloc(sizeof(dbcache_class));
	out->free = dbcache_free;
	out->put =  dbcache_put;
	out->get =  dbcache_get;
	int ret = 0;

	ret = db_create(&out->db, NULL, 0);
	ret = db_create(&out->sdb, NULL, 0);
	ret = db_create(&out->store, NULL, 0);

	ret = out->db->open(out->db,NULL,filename,NULL,DB_BTREE,DB_CREATE,0);

	char * storeFilename = malloc(strlen(filename)+6);
	sprintf(storeFilename,"%s_store",filename);
	ret = out->store->open(out->store,NULL,storeFilename,NULL,DB_BTREE,DB_CREATE,0);


	char * tindexFilename = malloc(strlen(filename)+6);
	sprintf(tindexFilename,"%s_tindx",filename);
	ret = out->tindex->open(out->tindex,NULL,secDbFile,NULL,DB_BTREE,DB_CREATE,0);


	ret = out->db->associate(out->db,NULL,out->tindex,dbcache_secondary_key,0);


	return out;
}
