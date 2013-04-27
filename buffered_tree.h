#ifndef WHEAT_BUFFERED_TREE
#define WHEAT_BUFFERED_TREE

// Normally, L2 Cache line size is 128/256 bytes. 16 containers can
// occupy 128 bytes
#define BFTREE_DEFAULT_CONTAINER       16
#define BFTREE_CONTAINER_THRESHOLD     16
#define BFTREE_PAYLOAD_THRESHOLD       100

#define BF_OK                          0
#define BF_WRONG                       (-1)

struct bftree;
typedef int (*key_compare_func)(const void *key1, const void *key2);

struct bftree_opts {
    void *(*key_dup)(const void *key);
    void *(*val_dup)(const void *obj);
    key_compare_func key_compare;
    void (*key_destructor)(void *key);
    void (*val_destructor)(void *obj);
};

struct bftree *bftree_create(struct bftree_opts *opts);
void bftree_free(struct bftree *tree);
int bftree_put(struct bftree *tree, void *key, void *val);
void *bftree_get(struct bftree *tree, void *key);
int bftree_del(struct bftree *tree, void *key);

#endif
