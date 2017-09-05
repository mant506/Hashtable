#include "htable.h"
#include "container.h"
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 3877

int main (int argc, char **argv) {
    FILE *infile;
    htable t = htable_new(DEFAULT_SIZE);
    char word[256];
    if (argc > 1) {
        if (NULL == (infile = fopen(argv[1], "r"))) {
            fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[1]);
            return EXIT_FAILURE;
        }
        while (getword(word, sizeof word, infile) != EOF) {
            htable_insert(t, word, 'r');
        }
        while (getword(word, sizeof word, stdin) != EOF) {
            if (htable_search(t, word) != 1) {
                printf("%s not spelt correctly\n", word);
            }
        }
        htable_free(t);
    }
    return EXIT_SUCCESS;
}
