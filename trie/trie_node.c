#include "trie_node.h"

struct _trie_node_t {
    char prefix;

    trie_node_t next;
    trie_node_t link;
}