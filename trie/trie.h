#ifndef _TRIE_H_
#define _TRIE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _trie_t trie_t;
typedef trie_t* trie_ref_t;

trie_ref_t create_trie();

void insert(trie_ref_t self, const char* value, const char* key);
const char* search(trie_ref_t self, const char* key);

void destroy_trie(trie_ref_t trie);

#ifdef __cplusplus
}
#endif

#endif