#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mylib.h"
#include "htable.h"
#include "container.h"

struct htablerec {
    container *containers;
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
    result->frequencies = emalloc(capacity * sizeof result->frequencies[0]);
    result->containers = emalloc(capacity * sizeof(*(result->containers)));
    for (i = 0; i < capacity; i++) {
        result->frequencies[i] = 0;
        result->containers[i] = NULL;
    }
    return result;                       
}

void htable_free(htable h) {
    unsigned int i;
    free(h->frequencies);
    for (i = 0; i < h->capacity; i++) {
        if (NULL != h->containers[i]) {
            container_free(h->containers[i]);
        }
    }
    free(h->containers);
    free(h);
}

int htable_insert(htable h, char *str) {
    
    unsigned int index = htable_word_to_int(str) % h->capacity;
    int step = htable_step(h, index);
    unsigned int i = index;
    if (h->containers[index] == NULL) {
        container_add(h->containers[index], str); 
        h->frequencies[index] = 1;
        h->num_keys++;
        return 1;
    } else if (container_search(h->containers[index], str) == 1) {
        container_add(h->containers[index], str);
        h->frequencies[index]++;
        return h->frequencies[index];
    } else {
        do {
            index = (index + step) % h->capacity;
        } while (h->containers[index] != NULL && container_search(h->containers[index], str) != 1  && index != i);
        if (h->containers[index] == NULL) {
            container_add(h->containers[index], str); 
            h->frequencies[index] = 1;
            h->num_keys++;
        } else if (container_search(h->containers[index], str)) {
            container_add(h->containers[index], str); 
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
        if (h->frequencies[i] != 0) {
            fprintf(stream, "%d ", h->frequencies[i]);
            container_print(h->containers[i], print_word);
        }
    }
}

int htable_search(htable h, char *str) {
    unsigned int collisions = 0;
    unsigned int index = htable_word_to_int(str) % h->capacity;
    int step = htable_step(h, index);
    unsigned int i = index;
    while (h->containers[index] != NULL && container_search(h->containers[index], str) != 1  && index != i) {
        index = (index + step) % h->capacity;
        collisions++;
    }
    if (collisions >= h->capacity) {
        return 0;
    } else {
        return h->frequencies[index];
    }
}

