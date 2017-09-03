#ifndef CONTAINER_H_
#define CONTAINER_H_

typedef enum container_e {FLEX_ARRAY, RED_BLACK_TREE} container_t;

extern void      container_add(container c, char *word);
extern container container_new_rbt();
extern container container_new_flexarray();
extern container container_free(container c);
extern void      container_print(container c);
extern int       container_search(container c, char *target);      
extern container container_delete(container c, char *target);

#endif