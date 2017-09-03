#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"
#include "rbt.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum { RED, BLACK } rbt_colour;

struct rbt_node {
    char *key;
    rbt_colour colour;
    int count;
    rbt left;
    rbt right;
};

rbt rbt_new() {
    rbt new = NULL;
    return new;
}

int rbt_search(rbt b, char *str) {
    
    if (NULL == b) {
        return 0;
    } else if (strcmp(b->key,str) == 0) {
        return 1;
    } else if (strcmp(b->key,str) > 0) {
        rbt_search(b->left,str);
    } else if (strcmp(b->key,str) < 0) {
        rbt_search(b->right,str);
    }
    return 1;
}

static rbt right_rotate(rbt b) {
    rbt temp = b;
    b = b->left;
    temp->left = b->right;
    b->right = temp;
    return b;
}

static rbt left_rotate(rbt b) {
    rbt temp = b;
    b = b->right;
    temp->right = b->left;
    b->left = temp;
    return b;
}

static rbt rbt_fix(rbt b) {
    if (IS_RED(b->left) && IS_RED(b->left->left)) {
        if (IS_RED(b->right)) {
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        } else if (IS_BLACK(b->right)) {
            b = right_rotate(b);
            b->colour = BLACK;
            b->right->colour = RED;
        }
    } else if (IS_RED(b->left) && IS_RED(b->left->right)) {
        if (IS_RED(b->right)) {
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        } else if (IS_BLACK(b->right)) {
            b->left = left_rotate(b->left);
            b = right_rotate(b);
            b->colour = BLACK;
            b->right->colour = RED;
        }
    } else if (IS_RED(b->right) && IS_RED(b->right->left)) {
        if (IS_RED(b->left)) {
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        } else if (IS_BLACK(b->left)) {
            b->right = right_rotate(b->right);
            b = left_rotate(b);
            b->colour = BLACK;
            b->left->colour = RED;
        }
    } else if (IS_RED(b->right) && IS_RED(b->right->right)) {
        if (IS_RED(b->left)) {
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        } else if (IS_BLACK(b->left)) {
            b = left_rotate(b);
            b->colour = BLACK;
            b->left->colour = RED;
        }
    }
    return b;
}

rbt rbt_insert(rbt b, char *str) {
    if (NULL == b) {
        b = emalloc(sizeof *(b));
        b->colour = RED;
        b->left = NULL;
        b->right = NULL;
        b->count = 1;
        b->key = emalloc((strlen(str) + 1) * sizeof(b->key));
        strcpy(b->key, str);
        printf("%s inserted\n", str);
        return b;
    } else if (strcmp(b->key,str) > 0) {
        printf("Go left\n");
        b->left = rbt_insert(b->left,str);
    } else if (strcmp(b->key,str) < 0) {
        printf("Go right\n");
        b->right = rbt_insert(b->right,str);
    } else if (strcmp(b->key,str) == 0) {
        b->count++;
    }
    b = rbt_fix(b);
    return b;
}

rbt rbt_free(rbt b) {
    if (NULL == b) {
        return b;
    } 
    b->left = rbt_free(b->left);
    b->right = rbt_free(b->right);
    free(b->key);
    free(b);
    return b;
}

void rbt_inorder(rbt b, void f(char *str)) {
    if (NULL == b) {
        return;
    }
    rbt_inorder(b->left,f);
    f(b->key);
    rbt_inorder(b->right,f);
}

void rbt_preorder(rbt b, void f(char *str1, char *str2, int count)) {
    if (NULL == b) {
        return;
    }
    if (IS_RED(b)) {
        f(b->key, "red", b->count);
    } else if (IS_BLACK(b)) {
        f(b->key, "black", b->count);
    }
    rbt_preorder(b->left,f);
    rbt_preorder(b->right,f);
}

rbt rbt_delete(rbt b, char *str) {
    rbt t;
    rbt sucessor = NULL;
    if (b == NULL) {;
        return NULL;
    }
    if (strcmp(b->key,str) == 0) {
        if (NULL == b->left && NULL == b->right) {
            free(b->key);
            free(b);
            return NULL;
        } else if (NULL != b->right && NULL != b->left) {;
            t = b;
            sucessor = b->right;
            while (NULL != sucessor->left) {
                t = sucessor;
                sucessor = sucessor->left;
            }
            t->left = sucessor->right;
            free(b->key);
            b->key = sucessor->key;
            free(sucessor);
            return b;
            
        } else if (NULL != b->left) {
            t = b->left;
            free(b->key);
            free(b);
            return t;
        } else if (NULL != b->right) {;
            t = b->right;
            free(b->key);
            free(b);
            return t;
        }                                               
    } else if (strcmp(b->key,str) > 0) {
        b->left = rbt_delete(b->left,str);
        return b;
    } else if (strcmp(b->key,str) < 0) {;
        b->right = rbt_delete(b->right,str);
        return b;
    }
    return b;
}





