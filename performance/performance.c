#include <sys/time.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "redis-dict.h"
#include "../buffered_tree.h"
#include "sds.h"

#define get_seconds(start, end) ((end.tv_sec-start.tv_sec)+((double)(end.tv_usec-start.tv_usec))/1000000)

unsigned int dictSdsHash(const void *key) {
    return dictGenHashFunction((unsigned char*)key, sdslen((char*)key));
}

void dictSdsDestructor(void *privdata, void *val)
{
    sdsfree(val);
}

int dictSdsKeyCompare(void *privdata, const void *key1,
        const void *key2)
{
    int l1,l2;
    DICT_NOTUSED(privdata);

    l1 = sdslen((sds)key1);
    l2 = sdslen((sds)key2);
    if (l1 != l2) return 0;
    return memcmp(key1, key2, l1) == 0;
}


dictType sdsdict_type = {
    dictSdsHash,             /* hash function */
    NULL,                       /* key dup */
    NULL,                       /* val dup */
    dictSdsKeyCompare,       /* key compare */
    dictSdsDestructor,  /* key destructor */
    dictSdsDestructor   /* val destructor */
};

void redis_add(dict *d, int times)
{
    int i;
    sds key, val;
    char buf[20];

    for (i = 0; i < times; ++i) {
        snprintf(buf, 20, "key%d", i);
        key = sdsnew(buf);
        snprintf(buf, 20, "val%d", i);
        val = sdsnew(buf);
        assert(dictAdd(d, key, val) == DICT_OK);
    }
}

int bftreeSdsKeyCompare(const void *key1, const void *key2)
{
    int l1,l2;

    l1 = sdslen((sds)key1);
    l2 = sdslen((sds)key2);
    if (l1 != l2) return l1 < l2 ? -1 : 1;
    return memcmp(key1, key2, l1);
}

struct bftree *bftree_add(struct bftree *tree, int times)
{
    int i;
    char buf[20];
    sds key, val;

    for (i = 0; i < times; ++i) {
        snprintf(buf, 20, "key%d", i);
        key = sdsnew(buf);
        snprintf(buf, 20, "val%d", i);
        val = sdsnew(buf);

        assert(bftree_put(tree, key, val) == BF_OK);
    }
    return tree;
}

void bftree_fetch(struct bftree *tree, int times)
{
    int i, j;
    char buf[20];
    sds key, val;

    srand(1992);
    for (i = 0; i < times; ++i) {
        j = rand() % times;
        snprintf(buf, 20, "key%d", j);
        key = sdsnew(buf);

        assert(bftree_get(tree, key));
        sdsfree(key);
    }
}

void redis_fetch(dict *d, int times)
{
    int i, j;
    char buf[20];
    sds key, val;

    srand(1992);
    for (i = 0; i < times; ++i) {
        j = rand() % times;
        snprintf(buf, 20, "key%d", j);
        key = sdsnew(buf);

        assert(dictFetchValue(d, key));
        sdsfree(key);
    }
}

void redis_del(dict *d, int times)
{
    int i, j;
    char buf[20];
    sds key, val;

    srand(1992);
    for (i = 0; i < times; ++i) {
        j = rand() % times;
        snprintf(buf, 20, "key%d", j);
        key = sdsnew(buf);

        dictDelete(d, key);
        sdsfree(key);
    }
}

void bftree_delele(struct bftree *tree, int times)
{
    int i, j;
    char buf[20];
    sds key, val;

    srand(1992);
    for (i = 0; i < times; ++i) {
        j = rand() % times;
        snprintf(buf, 20, "key%d", j);
        key = sdsnew(buf);

        bftree_del(tree, key);
    }
}

int main(int argc, const char *argv[])
{
    struct timeval start, end;
    double elapsed;
    dict *d;
    struct bftree *tree;
    const int times = 500;

    struct bftree_opts opt = {
        NULL, NULL, bftreeSdsKeyCompare, (void (*)(void*))sdsfree, (void (*)(void*))sdsfree
    };
    tree = bftree_create(&opt);

    d = dictCreate(&sdsdict_type, NULL);

    gettimeofday(&start, NULL);
    redis_add(d, times);
    gettimeofday(&end, NULL);
    elapsed = get_seconds(start, end);
    printf("redis add %d elements seconds: %f\n", times, elapsed);

    gettimeofday(&start, NULL);
    tree = bftree_add(tree, times);
    gettimeofday(&end, NULL);
    elapsed = get_seconds(start, end);
    printf("bftree add %d elements seconds: %f\n", times, elapsed);

    gettimeofday(&start, NULL);
    redis_fetch(d, times);
    gettimeofday(&end, NULL);
    elapsed = get_seconds(start, end);
    printf("redis get %d elements seconds: %f\n", times, elapsed);

    gettimeofday(&start, NULL);
    bftree_fetch(tree, times);
    gettimeofday(&end, NULL);
    elapsed = get_seconds(start, end);
    printf("bftree get %d elements seconds: %f\n", times, elapsed);

    gettimeofday(&start, NULL);
    redis_del(d, times);
    gettimeofday(&end, NULL);
    elapsed = get_seconds(start, end);
    printf("redis delete %d elements seconds: %f\n", times, elapsed);

    gettimeofday(&start, NULL);
    bftree_delele(tree, times);
    gettimeofday(&end, NULL);
    elapsed = get_seconds(start, end);
    printf("bftree delete %d elements seconds: %f\n", times, elapsed);

    bftree_free(tree);
    dictRelease(d);

    return 0;
}
