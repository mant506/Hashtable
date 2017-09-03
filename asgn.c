#include "htable.h"
#include "container.h"
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void) {
    htable t = htable_new(10, "-r");
    htable_free(t);
    return EXIT_SUCCESS;
}
