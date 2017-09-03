#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mylib.h"
#include "htable.h"

struct htablerec {
    char **keys;
    int *frequencies;
    int num_keys;
    unsigned int capacity;
};

static unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

htable htable_new(int capacity) {
    int i;
    htable result = emalloc(sizeof *(result));
    result->capacity = capacity;
    result->num_keys = 0;
    result->frequencies = emalloc(capacity*(sizeof result->frequencies[0]));
    result->keys = emalloc(capacity*(sizeof result->keys[0]));
    for (i = 0; i < capacity; i++) {
        result->keys[i] = NULL;
        result->frequencies[i] = 0;
    }
    return result;                       
}

void htable_free(htable h) {
    unsigned int i;
    free(h->frequencies);
    for (i = 0; i < h->capacity; i++) {
        free(h->keys[i]);
    }
    free(h->keys);
    free(h);
}

int htable_insert(htable h, char *str) {
    
    unsigned int index = htable_word_to_int(str) % h->capacity;
    int step = htable_step(h, index);
    unsigned int i = index;
    if (h->keys[index] == NULL) {
        h->keys[index] = emalloc((strlen(str)+1)*sizeof(h->keys[index][0]));
        strcpy(h->keys[index],str);
        h->frequencies[index] = 1;
        return 1;
    } else if (strcmp(h->keys[index],str) == 0) {
        h->frequencies[index]++;
        return h->frequencies[index];
    } else {
        do {
            index = (index + step) % h->capacity;
        } while (h->keys[index] != NULL && strcmp(h->keys[index], str) != 0  && index != i);
        if (h->keys[index] == NULL) {
            h->keys[index] = emalloc((strlen(str)+1)*sizeof(h->keys[index][0]));
            strcpy(h->keys[index],str);
            h->frequencies[index] = 1;
        } else if (strcmp(h->keys[index],str) == 0) {
            h->frequencies[index]++;
            return h->frequencies[index];
        } else {
            return 0;
        }
    }
    return 1;
}

void htable_print(htable h, FILE *stream) {
    unsigned int i;
    for (i = 0; i < h->capacity; i++) {
        if (h->frequencies[i] != 0)
            fprintf(stream, "%d %s\n", h->frequencies[i], h->keys[i]);
    }
}

int htable_search(htable h, char *str) {
    unsigned int collisions = 0;
    unsigned int index = htable_word_to_int(str) % h->capacity;
    int step = htable_step(h, index);
    unsigned int i = index;
    while (h->keys[index] != NULL && strcmp(h->keys[index],str) != 0 && index != i) {
        index = (index + step) % h->capacity;
        collisions++;
    }
    if (collisions >= h->capacity) {
        return 0;
    } else {
        return h->frequencies[index];
    }
}

