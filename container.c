#include "mylib.h"
#include "flexarray.h"
#include "rbt.h"
#include "container.h"

struct containerrec {
	container_t type;
	void *contents;
};

void container_add(container_t c, char *word) {
	if (c->type == RED_BLACK_TREE) {
		c->contents = rbt_insert(c->contents, word);
	} else {
		flexarray_append(c->contents, word);
	}
}

container container_new_rbt() {
		return rbt_new();
}
container container_new_flexarray() {
	return flexarray_new();
}

container container_free(container c) {
	if (c->type == RED_BLACK_TREE) {
		return rbt_free(c->contents);
	} else {
		flexarray_free(c->contents);
		return NULL;
	}
}

int container_search(container c) {
	if (c->type == RED_BLACK_TREE) {
		return rbt_search(c->contents, char *target);
	} else {
		return flexarray_is_present(c->contents, char *target);
	}
}

void container_print(container c, char *word) {
	if (c->type == RED_BLACK_TREE) {
		c->contents = rbt_preorder(c->contents, print_colour_key_count);
	} else {
		flexarray_visit(c->contents, print_word);
	}
}

container container_delete(container c, char *word) {
	if (c->type == RED_BLACK_TREE) {
		c->contents = rbt_delete(c->contents, word);
	}
}
    
extern void      container_delete(container c, char *target);