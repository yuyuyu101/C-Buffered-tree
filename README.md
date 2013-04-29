C-Buffered-tree
===========

[Buffered-tree](http://www.cs.cmu.edu/~guyb/realworld/slidesF10/buffertree.pdf)
is a write-optimized data structure. It can full utilize modern large memory.
This buffered-tree is used to as a dictionary type and supports Put, Delete, Get
these methods.

As we know, developers love implementing dictionary type using hash. Hash can 
get excellent performance and simple to implement and use. But the conflict is
the pain of hash implementation. Using buffered-tree, we can implement a much
better space utilization.

Google implements a [B-tree version](https://code.google.com/p/cpp-btree/w/list)
in order to replace the c++ std library version  We can find that B-tree can get
amazing performance compared with c++ std.

I will deliver my buffered-tree version compared to Google version and other
hash implementation.

More data structure supporting based on buffered-tree is on going.

Usage
===========

see buftree_example.c

Customizer
===========

C-Buffered-tree is aimed to provide a general dictionary structure to users.
So users can easily expand more types. You can find example on the bottom of
buffer_tree.c of "Map Area" section.

API
===========

struct bftree *bftree_create(struct bftree_opts *opts);
void bftree_free(struct bftree *tree);
int bftree_put(struct bftree *tree, void *key, void *val);
void *bftree_get(struct bftree *tree, void *key);
int bftree_del(struct bftree *tree, void *key);
// Ineffective count implementation!!!! Don't call it if big tree
int bftree_count(struct bftree *tree);

// Iterator is in ordering!
struct bftree_iterator *bftree_get_iterator(struct bftree *tree);
struct payload *bftree_next(struct bftree_iterator *iter);
void bftree_free_iterator(struct bftree_iterator *iter);
