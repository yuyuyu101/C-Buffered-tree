#ifndef BUFTREE_MAP_H
#define BUFTREE_MAP_H

#include "buffered_tree.h"

struct bftree *bftmap_create();
void bftmap_free(struct bftree *tree);
int bftmap_put(struct bftree *tree, char *key, size_t key_len, void *val);
void *bftmap_get(struct bftree *tree, char *key, size_t key_len);
int bftmap_del(struct bftree *tree, char *key, size_t key_len);

struct bftree *bftmap_nocopy_create();
void bftmap_nocopy_free(struct bftree *tree);
int bftmap_nocopy_put(struct bftree *tree, char *key, size_t key_len, void *val);
void *bftmap_nocopy_get(struct bftree *tree, char *key, size_t key_len);
int bftmap_nocopy_del(struct bftree *tree, char *key, size_t key_len);

#endif
