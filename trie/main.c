#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"

extern size_t counter;
extern size_t node_size;

void load_binary() {
    FILE *f = fopen("output.bin", "rb");

    trie_ref_t trie = create_trie();


    unsigned long features_count = 0;
    fread(&features_count, sizeof(unsigned long), 1, f);

    printf("featires_count: %ld\n", features_count);

    for (size_t i = 0; i < features_count; ++i) {
        unsigned long key_size = 0;

        fread(&key_size, sizeof(unsigned long), 1, f);

        char* key = (char *)malloc(sizeof(char) * key_size + 1);
        fread(key, key_size, 1, f);
        key[key_size] = '\0';

        unsigned long samples_count = 0;
        fread(&samples_count, sizeof(unsigned long), 1, f);

        printf("samples_count: %ld\n", samples_count);

        printf("%s\n", key);

        for (size_t j = 0; j < samples_count; ++j) {
            unsigned long tokens_count = 0;
            fread(&tokens_count, sizeof(unsigned long), 1, f);

            char **tokens = (char **)malloc(sizeof(char *) * tokens_count);

            unsigned long sample_size = 0;

            for (size_t j = 0; j < tokens_count; ++j) {
                unsigned long token_size = 0;
                fread(&token_size, sizeof(unsigned long), 1, f);

                sample_size += token_size + 1;

                char* token = (char *)malloc(sizeof(char) * (token_size + 1));
                token[token_size] = '\0';

                fread(token, token_size, 1, f);

                tokens[j] = token;
            }

            char *sample = (char *)malloc(sizeof(char) * (sample_size + 1));
            sample[0] = '\0';
            sample[sample_size] = '\0';

            for (size_t j = 0; j < tokens_count; ++j) {
                sample = strcat(sample, tokens[j]);
                free(tokens[j]);
            }

            free(tokens);

            insert(trie, key, sample);

            free(sample);

            // char* sample = (char *)malloc(sizeof(char) * sample_size + 1);
            // fread(sample, sample_size, 1, f);
            // sample[sample_size] = '\0';

            // printf("sample: %s\n", sample);

            // insert(trie, key, sample);

            // free(sample);
        }

        free(key);
    }

    fclose(f);

    printf("Ready: %zu, %zu\n", counter, node_size);

    while (1) {
        char buff[255];

        scanf("%s", buff);

        printf("%s\n", search(trie, buff));
    }

    destroy_trie(trie);
}


int main(int argc, char *argv[]) {
    // load_binary();
    trie_ref_t trie = create_trie();

    // // insert(trie, "value", "key");
    insert(trie, "value1", "key");

    printf("%s\n", search(trie, "key"));

    destroy_trie(trie);
    return 0;
}