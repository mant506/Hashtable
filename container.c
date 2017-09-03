#include "mylib.h"
#include "flexarray.h"
#include "rbt.h"
#include "container.h"

struct containerrec {
    container_t type;
    void *contents;
};

void container_add(container c, char *word) {
    if (c->type == RED_BLACK_TREE) {
        c->contents = rbt_insert(c->contents, word);
    } else {
        flexarray_append(c->contents, word);
    }
}

container container_new_rbt() {
    container result = emalloc (sizeof *(result));
    result->type = RED_BLACK_TREE;
    result->contents = rbt_new();
    return result;
}
container container_new_flexarray() {
    container result = emalloc (sizeof *(result));
    result->type = FLEX_ARRAY;
    result->contents = flexarray_new();
    return result;
}

container container_free(container c) {
    if (c->type == RED_BLACK_TREE) {
        rbt_free(c->contents);
        free(c);
        return c;
    } else {
        flexarray_free(c->contents);
        free(c);
        return c;
    }
}

int container_search(container c, char *target) {
    if (c->type == RED_BLACK_TREE) {
        return rbt_search(c->contents, target);
    } else {
        return flexarray_is_present(c->contents, target);
    }
}

void container_print(container c, void f(char *word)) {
    if (c->type == RED_BLACK_TREE) {
        rbt_preorder(c->contents, f);
    } else {
        flexarray_visit(c->contents, f);
    }
}
