#ifndef CONTAINER_H_
#define CONTAINER_H_

typedef enum container_e {FLEX_ARRAY, RED_BLACK_TREE} container_t;
typedef struct containerrec *container;

extern void      container_add(container c, char *word);
extern container container_new_rbt();
extern container container_new_flexarray();
extern container container_free(container c);
extern void      container_print(container c, void f(char *word));
extern int       container_search(container c, char *target);      

#endif
