#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"


ROOT* linkedlist_init(void){
    ROOT* root = (ROOT*)malloc(sizeof(ROOT));
    root->listlen = 0;
    root->lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(root->lock, NULL);
    root->node_root = NULL;
    
    return root;
}

NODE* create_node(char* key, void* value){
    NODE* node = (NODE*)malloc(sizeof(NODE));
    #ifdef DEBUG
    printf("> create node:     %d\n", node);
    #endif
    node->key = key;
    node->value = value;
    node->next = NULL;
    
    return node;
}

void free_node(NODE* node){
    if (node == NULL)
        return;
    #ifdef DEBUG
    printf("<<< free:%d\n", node);
    #endif
    free(node->key);
    free(node->value);
    free(node);
    node = NULL;
}
void free_root(ROOT* root){
    if (root == NULL)
        return;
    #ifdef DEBUG
    printf("<<< free:%d\n", root);
    #endif
    free(root);
}

int linkedlist_add(ROOT* root, char* key_in, void* value_in){
    // lock
    pthread_mutex_lock(root->lock);
    if (root == NULL){
        pthread_mutex_unlock(root->lock);
        return LIST_ROOT_IS_NULL;
    }
    if ((root->listlen == 0) && (root->node_root == NULL)){ // 如果list为空，直接添加到node_root，然后退出
        NODE* new_node = create_node(key_in, value_in);
        root->node_root = new_node;
        root->listlen += 1;

        pthread_mutex_unlock(root->lock);
        return LIST_OK;
    }
    NODE* node = root->node_root;
    NODE* lastnode = node;
    while(1){
        if (node == NULL){
            break;
        }
        if (strcmp(node->key, key_in) == 0){ // 存在相同的key，退出
            pthread_mutex_unlock(root->lock);
            return LIST_KEY_EXIST;
        }
        lastnode = node;    // 保存当前node
        node = node->next;  // 当前node后移
    }
    lastnode->next = create_node(key_in, value_in);
    root->listlen += 1;

    pthread_mutex_unlock(root->lock);
    return LIST_OK;
}

int linkedlist_get(ROOT* root, char* key_in, void** value_out){
    pthread_mutex_lock(root->lock);
    if (root == NULL){
        pthread_mutex_unlock(root->lock);
        return LIST_ROOT_IS_NULL;
    }
    NODE* node = root->node_root;
    while(1){
        if (node == NULL){
            break;
        }
        else {
            #ifdef DEBUG
            printf("|||   node addr:      %d, key: %s, vlaue: %s\n", node, node->key, node->value);
            #endif
            if (strcmp(node->key, key_in) == 0){
                (*value_out) = node->value;
                pthread_mutex_unlock(root->lock);
                return LIST_OK;
            }
            node = node->next;
        }
    }

    pthread_mutex_unlock(root->lock);
    return LIST_KEY_NOTEXIST;
}

int linkedlist_traverse(ROOT* root){
    // lock
    pthread_mutex_lock(root->lock);
    printf(">>>>>> traverse <<<<<<\n");
    if (root == NULL){
        pthread_mutex_unlock(root->lock);
        return LIST_ROOT_IS_NULL;
    }
    NODE* node = root->node_root;
    while(1){
        if (node == NULL){
            break;
        }
        else {
            printf(">>> node addr: %d, key: %s\n", node, node->key);
            node = node->next;
        }
    }
    pthread_mutex_unlock(root->lock);
    printf(">>>>>> traverse over <<<<<<\n");
    return LIST_OK;

}

int linkedlist_empty(ROOT** root){
    // lock
    pthread_mutex_lock((*root)->lock);
    if ((*root) == NULL){
        pthread_mutex_unlock((*root)->lock);
        return LIST_ROOT_IS_NULL;
    }
    NODE* node = (*root)->node_root;
    
    
    while(1){
        if (node == NULL){
            break;
        }
        else{
            NODE* next = node->next;
            free_node(node);
            node = next;
        }
    }
    pthread_mutex_t *list_lock = (*root)->lock;
    free_root((*root));
    (*root) = NULL;
    pthread_mutex_unlock(list_lock);
    pthread_mutex_destroy(list_lock);
    free(list_lock);

    return LIST_OK;
}

int linkedlist_del(ROOT* root, char* key_in){
    // lock
    pthread_mutex_lock(root->lock);
    if (root == NULL){
        // unlock
        pthread_mutex_unlock(root->lock);
        return LIST_ROOT_IS_NULL;
    }

    NODE* node = root->node_root;
    NODE* lastnode = NULL;
    while(1){
        if (node == NULL){
            break;
        }
        else {
            if (strcmp(node->key, key_in) == 0){
                #ifdef DEBUG
                printf("\n>>> DEL node: %d, key: %s\n\n", node, node->key);
                #endif
                if (node == root->node_root){ // 当删除的Node为第一个Node时
                    root->node_root = node->next;
                    root->listlen -= 1;
                    free_node(node);
                }
                else{ // 当删除的Node在第一个Node之后
                    lastnode->next = node->next;
                    root->listlen -= 1;
                    free_node(node);
                }
                pthread_mutex_unlock(root->lock);
                return LIST_OK;
            }
            lastnode = node;
            node = node->next;
        }
    }

    pthread_mutex_unlock(root->lock);
    return LIST_KEY_NOTEXIST;
}
