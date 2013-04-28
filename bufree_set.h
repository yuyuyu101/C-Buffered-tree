#ifndef BFTREE_SET_H
#define BFTREE_SET_H

#include "buffered_tree.h"

struct bftree *bftset_create();
void bftset_free(struct bftree *tree);
int bftset_put(struct bftree *tree, char *key, size_t key_len);
void *bftset_get(struct bftree *tree, char *key, size_t key_len);
int bftset_del(struct bftree *tree, char *key, size_t key_len);

#endif
