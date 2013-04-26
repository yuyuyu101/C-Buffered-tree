Buffered-tree
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
