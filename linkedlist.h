#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <pthread.h>

typedef struct linkedlist_node
{
    char* key;
    void* value;
    struct linkedlist_node* next;
}NODE;

typedef struct linkedlist_root
{
    int listlen;
    pthread_mutex_t *lock;
    struct linkedlist_node* node_root;
}ROOT;

//#define DEBUG

#define LIST_OK               0
#define LIST_ROOT_IS_NULL    -1
#define LIST_KEY_EXIST       -2
#define LIST_KEY_NOTEXIST    -3



ROOT* linkedlist_init(void);

int linkedlist_add(ROOT* root, char* key_in, void* value_in);

int linkedlist_get(ROOT* root, char* key_in, void** value_out);

int linkedlist_del(ROOT* root, char* key_in);

int linkedlist_traverse(ROOT* root);

int linkedlist_empty(ROOT** root);

#endif