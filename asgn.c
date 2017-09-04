#include "htable.h"
#include "container.h"
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void) {
    htable t = htable_new(10);
    htable_insert(t, "hey", 'r');
    htable_insert(t, "splendid", 'r');
    htable_insert(t, "fab", 'r');
    htable_insert(t, "wing", 'r');
    htable_insert(t, "check", 'r');
    /*
    if (htable_search(t, "check") == 1) {
        printf("check found\n");
    } else {
        printf("Not found\n");
    }
    */
    htable_print(t, stdout);
    htable_free(t);
    return EXIT_SUCCESS;
}
