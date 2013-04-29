#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bftree_map.h"
#include "bftree_set.h"

void bftmap_example()
{
    struct bftree *tree;
    int i, len;
    char buf[100];
    char *val;
    struct bftree_iterator *iter;
    int count;

    tree = bftmap_create();
    for (i = 0; i < 1000; i++) {
        len = snprintf(buf, 100, "key%d", i);
        val = malloc(100);
        snprintf(val, 100, "val%d", i);
        bftmap_put(tree, buf, len, val);
    }

    assert(bftree_count(tree) == 1000);

    count = 0;
    iter = bftree_get_iterator(tree);
    while (bftree_next(iter) != NULL)
        count++;
    bftree_free_iterator(iter);
    assert(count == 1000);

    for (i = 0; i < 10000; i++) {
        len = snprintf(buf, 100, "key%d", i);
        bftmap_del(tree, buf, len);
    }

    for (i = 0; i < 1000; i++) {
        len = snprintf(buf, 100, "key%d", i);
        bftmap_get(tree, buf, len);
    }


    bftmap_free(tree);
}

void bftset_example()
{
    struct bftree *tree;
    int i, len;
    char buf[100];
    char *val;

    tree = bftset_create();
    for (i = 0; i < 10000; i++) {
        len = snprintf(buf, 100, "key%d", i);
        val = malloc(100);
        snprintf(val, 100, "val%d", i);
        bftset_put(tree, buf, len);
    }

    for (i = 0; i < 10000; i++) {
        len = snprintf(buf, 100, "key%d", i);
        bftset_del(tree, buf, len);
    }

    for (i = 0; i < 10000; i++) {
        len = snprintf(buf, 100, "key%d", i);
        bftset_get(tree, buf, len);
    }

    bftmap_free(tree);
}

int main()
{
    bftmap_example();
    bftset_example();
}
