typedef struct dbcache_class{
    void (*free)(void*);
    void (*put)(void*,char*,char*);
    char* (*get)(void*,char*);
    DB *db;
    DB *sdb;
    DB *tindex;
    DB *store;
} dbcache_class;


dbcache_class * dbcache_class_new(char * filename);
int dbcache_secondary_key(DB *sdbp,const DBT *pkey,const DBT *pdata,DBT *skey);
