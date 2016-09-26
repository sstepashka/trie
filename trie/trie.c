#include "trie.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**/

typedef struct _trie_node_t trie_node_t;
typedef trie_node_t* trie_node_ref_t;

trie_node_ref_t create_node(char prefix);
void destroy_node(trie_node_ref_t node);

struct _trie_node_t {
    trie_node_ref_t next;
    trie_node_ref_t link;

    char* value;

    char prefix;
};

struct _trie_t {
    trie_node_ref_t root;
};

/**/

trie_ref_t create_trie() {
    trie_ref_t trie = (trie_ref_t)malloc(sizeof(trie_t));

    trie->root = create_node('\0');

    return trie;
}

void insert(trie_ref_t self, const char* value, const char* key) {
    size_t p = 0;
    size_t size = strlen(key);

    trie_node_ref_t node = self->root;

    while (node && p < size) {
        while(node->next && node->prefix != key[p]) {
            node = node->next;
        }

        if (node->prefix == key[p]) {
            if (size - 1 == p) {
                break;
            } else {
                if (node->link) {
                    node = node->link;
                } else {
                    trie_node_ref_t link = create_node(key[p]);
                    node->link = link;

                    node = link;
                }
            }
        } else {
            node->next = create_node(key[p]);
            node = node->next;

            continue;
        }

        ++ p;
    }

    if(node) {
        char *new_value = (char*)malloc((strlen(value) + 1) * sizeof(char));
        new_value[strlen(value)] = '\0';

        strcpy(new_value, value);

        node->value = new_value;
        node->value = value;
    }
}

const char* search(trie_ref_t self, const char* key) {
    size_t p = 0;
    size_t size = strlen(key);

    trie_node_ref_t node = self->root;

    while (node && p < size) {
        while(node->next && node->prefix != key[p]) {
            node = node->next;
        }

        if (node->prefix == key[p]) {
            if (size - 1 == p) {
                return node->value;
            } else {
                node = node->link;
            }
        } else {
            return NULL;
        }

        ++ p;
    }

    return NULL;
}

void destroy_trie(trie_ref_t trie) {
    free(trie);
}

/**/

size_t counter = 0;
size_t node_size = 0;

trie_node_ref_t create_node(char prefix) {
    trie_node_ref_t node = (trie_node_ref_t)malloc(sizeof(trie_node_t));

    node->prefix = prefix;

    node->value = NULL;
    node->next = NULL;
    node->link = NULL;

    ++counter;
    node_size = sizeof(trie_node_t);

    return node;
}

void destroy_node(trie_node_ref_t node) {
    if(node->value) {
        free(node->value);
    }

    free(node);
}
