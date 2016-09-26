#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

void load() {
    FILE *f = fopen("output.bin", "rb");

    map<string, string> gazetteers;

    // trie_ref_t trie = create_trie();


    unsigned long features_count = 0;
    fread(&features_count, sizeof(unsigned long), 1, f);

    // features_count = 30;

    for (size_t i = 0; i < features_count; ++i) {
        unsigned long key_size = 0;

        fread(&key_size, sizeof(unsigned long), 1, f);

        char* key = (char *)malloc(sizeof(char) * key_size + 1);
        fread(key, key_size, 1, f);
        key[key_size] = '\0';

        unsigned long samples_count = 0;
        fread(&samples_count, sizeof(unsigned long), 1, f);

        // printf("%s\n", key);

        for (size_t j = 0; j < samples_count; ++j) {
            unsigned long sample_size = 0;
            fread(&sample_size, sizeof(unsigned long), 1, f);

            char* sample = (char *)malloc(sizeof(char) * sample_size + 1);
            fread(sample, sample_size, 1, f);
            sample[sample_size] = '\0';

            // printf("\t%s\n", sample);

            // add_value_to_key(trie, key, sample);
            // add_value_to_key(trie, "1", sample);

            gazetteers[sample] = key;

            free(sample);
        }

        free(key);
    }

    fclose(f);

    cout << "Ready" << endl;

    while (1) {
        char buff[255];

        scanf("%s", buff);

        printf("%s\n", gazetteers[buff].c_str());
    }

}

int main(int argc, char* argv[]) {
    load();
    return 0;
}