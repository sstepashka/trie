#ifndef _TRIE_NODE_H_
#define _TRIE_NODE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _trie_node_t trie_node_t;
typedef trie_node_t* trie_node_ref_t;

trie_node_ref_t create_node(char prefix);

void destroy_node(trie_node_ref_t node);

#ifdef __cplusplus
}
#endif

#endif