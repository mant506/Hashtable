#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    char **items;
};

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}
static void insertion_sort(char **words, int n) {
    int i;
    for (i = 1; i < n; i++) {   
        char *key = words[i];
        int index = i;
        while (index > 0 && strcmp(words[index-1],key) > 0) {
            index--;
            words[index+1] = words[index];
        }
        words[index] = key;        
    }
}

int flexarray_is_present(flexarray f, char *target) {
	int i;
	for (i = 0; i < f->itemcount; i++) {
		if (strcmp(f->items[i], target) == 0) {
			return 1;
		}	
	}
	return 0;
}

void flexarray_visit(flexarray f, void func(char *str)) {
	int i;
	for (i = 0; i < f->itemcount; i++) {
		func(f->items[i]);
	}
}

void flexarray_append(flexarray f, char *item) {
    if (f->itemcount == f->capacity) {
        /* do the old "double the capacity" trick */
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    /* insert the item in the last free space */
    f->items[f->itemcount] = emalloc((strlen(item)+1) * sizeof f->items[0][0]);
    strcpy(f->items[f->itemcount], item);
    f->itemcount++;
}
void flexarray_print(flexarray f) {
    /* a "for" loop to print out each cell of f->items */
    int i;
    for (i = 0; i < f->itemcount; i++) {
        printf("%s ", f->items[i]); 
    }
    printf("\n");
}
void flexarray_sort(flexarray f) {
    insertion_sort(f->items, f->itemcount);
}
void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
    int i;
    for (i = 0; i < f->itemcount; i++) {
    	free(f->items[i]);
    }
    free(f);
}
